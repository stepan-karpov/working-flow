//go:build !solution

package main

import "fmt"

type Node struct {
	color int
	edges []string
}

func getReversed(prereqs map[string][]string) map[string]Node {
	reversed := make(map[string]Node)

	for subject, requisites := range prereqs {
		_, ok := reversed[subject]
		if !ok {
			reversed[subject] = Node{color: -1, edges: make([]string, 0)}
		}
		for _, req := range requisites {
			reversed[req] = Node{color: -1, edges: append(reversed[req].edges, subject)}
		}
	}

	return reversed
}

func Dfs(current_vertex string, graph map[string]Node, found_cycle *bool, sequence *[]string) {
	if *found_cycle {
		return
	}
	if graph[current_vertex].color == 2 {
		return
	}

	graph[current_vertex] = Node{1, graph[current_vertex].edges}

	for _, to := range graph[current_vertex].edges {
		if graph[to].color == 1 {
			*found_cycle = true
		} else {
			Dfs(to, graph, found_cycle, sequence)
		}
	}

	*sequence = append(*sequence, current_vertex)
	graph[current_vertex] = Node{2, graph[current_vertex].edges}
}

func GetCourseList(prereqs map[string][]string) []string {
	graph := getReversed(prereqs)

	// for k, v := range graph {
	// 	fmt.Printf("%v %v\n", k, v)
	// }

	sequence := make([]string, 0)
	found_cycle := false

	for k, v := range graph {
		if v.color == -1 {
			Dfs(k, graph, &found_cycle, &sequence)
		}
		if found_cycle {
			panic("hahaha")
		}
	}
	answer := make([]string, 0)
	for i := 0; i < len(sequence); i++ {
		answer = append(answer, sequence[len(sequence) - i - 1])
	}

	return answer
}

func main() {
	var naiveScience = map[string][]string{
		"A": {},
		"B": {"A"},
		"C": {"B", "A"},
		"D": {"B", "C"},
	}

	fmt.Println(GetCourseList(naiveScience))
}
