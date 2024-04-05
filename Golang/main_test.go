package main

import (
	"fmt"
	"reflect"
	"runtime"
	"testing"
	// "github.com/stretchr/testify/assert"
)

type T interface {
	Errorf(format string, args ...interface{})
	Helper()
	FailNow()
}


func CheckIfEqual(expected, actual interface{}) bool {
	if expected == struct{}{} && actual == struct{}{} {
		return true
	}
	return reflect.DeepEqual(expected, actual)
}

func WriteError(t T, expected, actual interface{}, msgAndArgs ...interface{}) {
	t.Helper()
	errMsg := "\n"
	_, file, line, _ := runtime.Caller(0)
	errMsg += "\t\tError Trace: " + file + ":" + fmt.Sprint(line) + "\n"
	errMsg += "\t\tError:       Equal\n"
	errMsg += "\t\tExpected:    " + fmt.Sprintf("%v", expected) + "\n"
	errMsg += "\t\tActual:      " + fmt.Sprintf("%v", actual) + "\n"
	errMsg += "\t\tTest:        " + "Ahaha" + "\n"
	if len(msgAndArgs) > 0 {
		errMsg += "Messages:    " + fmt.Sprintf("%v", msgAndArgs[0]) + "\n"
	}
	t.Errorf(errMsg)
	
	// fmt.Println(errMsg)
}

// AssertEqual checks that expected and actual are equal.
//
// Marks caller function as having failed but continues execution.
//
// Returns true iff arguments are equal.
func AssertEqual(t T, expected, actual interface{}, msgAndArgs ...interface{}) bool {
	if CheckIfEqual(expected, actual) {
		return true
	}
	WriteError(t, expected, actual, msgAndArgs...)
	return false
}

// AssertNotEqual checks that expected and actual are not equal.
//
// Marks caller function as having failed but continues execution.
//
// Returns true iff arguments are not equal.
func AssertNotEqual(t T, expected, actual interface{}, msgAndArgs ...interface{}) bool {
	if !CheckIfEqual(expected, actual) {
		return true
	}
	WriteError(t, expected, actual, msgAndArgs...)
	return false
}

// RequireEqual does the same as AssertEqual but fails caller test immediately.
func RequireEqual(t T, expected, actual interface{}, msgAndArgs ...interface{}) {
	if CheckIfEqual(expected, actual) {
		return
	}
	WriteError(t, expected, actual, msgAndArgs...)
	t.FailNow()
}

// RequireNotEqual does the same as AssertNotEqual but fails caller test immediately.
func RequireNotEqual(t T, expected, actual interface{}, msgAndArgs ...interface{}) {
	if !CheckIfEqual(expected, actual) {
		return
	}
	WriteError(t, expected, actual, msgAndArgs...)
	t.FailNow()
}

func TestAdd(t *testing.T) {
	AssertEqual(t, 1, 2, "1 != 2")

	// assert.Equal(t, 1, 2, "1 != 2")
}
