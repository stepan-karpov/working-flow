package program_examples

import (
	"errors"
)

func ErrorHandler(first_value int, second_value int) (int, int, error) {
	var err error

	if second_value == 0 {
		err = errors.New("Can't divide by Zero!")
		return 0, 0, err
	}

	fv, sv := Division(first_value, second_value)
	return fv, sv, err
}
