//go:build !solution

package main

import (
	"errors"
	"fmt"
	"strconv"
	"strings"
)

type Evaluator struct {
	newCommands map[string]string
	stack       []int
}

// NewEvaluator creates evaluator.
func NewEvaluator() *Evaluator {
	return &Evaluator{}
}

func PerformOperation(command *string, stack *[]int) error {
	if len(*stack) < 2 {
		return errors.New("insufficient operands on the stack")
	}
	operand2 := (*stack)[len(*stack)-1]
	operand1 := (*stack)[len(*stack)-2]
	*stack = (*stack)[:len(*stack)-2]

	switch *command {
	case "+":
		*stack = append(*stack, operand1+operand2)
	case "-":
		*stack = append(*stack, operand1-operand2)
	case "*":
		*stack = append(*stack, operand1*operand2)
	case "/":
		if operand2 == 0 {
			return errors.New("division by zero")
		}
		*stack = append(*stack, operand1/operand2)
	}
	return nil
}

func Open(to_open string, newCommands *map[string]string) string {
	result := to_open

	for key, value := range *newCommands {
		result = strings.ReplaceAll(result, key, value)
	}

	return result
}

func HandleCommand(command *string, index int,
	stack *[]int, newCommands *map[string]string,
	parts *[]string, e *Evaluator) (int, error) {
	if body, ok := (*newCommands)[strings.ToLower(*command)]; ok {
		err := GoJohnyGo(body, stack, e)
		if err != nil {
			return index + 1, err
		}
		return index + 1, nil
	}
	if *command == "+" || *command == "-" || *command == "*" || *command == "/" {
		err := PerformOperation(command, stack)
		if err != nil {
			return index, err
		}
		return index + 1, nil
	}
	if strings.ToLower(*command) == "dup" {
		if len(*stack) == 0 {
			return index, errors.New("stack is empty, nothing to dup")
		}
		*stack = append(*stack, (*stack)[len(*stack)-1])
		return index + 1, nil
	}
	if strings.ToLower(*command) == "over" {
		if len(*stack) <= 1 {
			return index, errors.New("stack is empty, nothing to over")
		}
		*stack = append(*stack, (*stack)[len(*stack)-2])
		return index + 1, nil
	}
	if strings.ToLower(*command) == "drop" {
		if len(*stack) == 0 {
			return index, errors.New("stack is empty, nothing to drop")
		}
		*stack = (*stack)[:len(*stack)-1]
		return index + 1, nil
	}
	if strings.ToLower(*command) == "swap" {
		if len(*stack) <= 1 {
			return index, errors.New("stack is empty, nothing to swap")
		}
		operand2 := (*stack)[len(*stack)-1]
		operand1 := (*stack)[len(*stack)-2]
		*stack = (*stack)[:len(*stack)-2]
		*stack = append(*stack, operand2)
		*stack = append(*stack, operand1)
		return index + 1, nil
	}
	if *command == ":" {
		name := (*parts)[index+1]
		index += 2
		newCommand := ""

		_, err := strconv.Atoi(name)
		if err == nil {
			return index + 1, errors.New("you try to redefine number")
		}

		fmt.Println("Defining ", name)
		for (*parts)[index] != ";" {
			newCommand += Open((*parts)[index], newCommands) + " "
			index++
		}
		// if name != "dup" && name != "swap" && name != "drop" && name != "over" {
			(*newCommands)[name] = newCommand[:len(newCommand)-1]
		// }
		return index + 1, nil
	}

	// assuming *command is int
	num, err := strconv.Atoi(*command)
	if err != nil {
		return index, errors.New("invalid number format")
	}
	*stack = append(*stack, num)
	return index + 1, nil
}

func GoJohnyGo(row string, stack *[]int, e *Evaluator) error {
	parts := strings.Split(row, " ")

	for index := 0; index < len(parts); {
		newIndex, err := HandleCommand(&parts[index], index, stack, &e.newCommands, &parts, e)
		if err != nil {
			return err
		}
		index = newIndex
	}

	return nil
}

// Process evaluates sequence of words or definition.
//
// Returns resulting stack state and an error.
func (e *Evaluator) Process(row string) ([]int, error) {
	if e.newCommands == nil {
		e.newCommands = make(map[string]string)
	}

	err := GoJohnyGo(row, &e.stack, e)

	if err != nil {
		return e.stack, err
	}

	fmt.Println(e.stack)
	return e.stack, nil
}

func main() {
	e := NewEvaluator()
	stack, _ := e.Process(": swap dup dup dup ; 1 swap")

	fmt.Println(stack)
}
