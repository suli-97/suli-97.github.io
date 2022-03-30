package main

import (
	"fmt"
	"strconv"
	"strings"
	"text/scanner"
)

var lexer scanner.Scanner
var tok rune
var text string

func lexInit(code string) {
	lexer.Init(strings.NewReader(code))
	lexNext()
}

func lexNext() {
	tok = lexer.Scan()
	text = lexer.TokenText()
	//fmt.Printf("tok: %s\n", text)
}

//E -> TE'
func expr() float64 {
	val := term()
	return exprPlus(val)
}

//E' -> +TE'|-TE'|ε
func exprPlus(val float64) float64 {
	switch tok {
	case '+':
		lexNext()
		val += term()
		return exprPlus(val)
	case '-':
		lexNext()
		val -= term()
		return exprPlus(val)
	default:
		return val
	}
}

//T -> FT'
func term() float64 {
	val := factor()
	return termPlus(val)
}

//T' -> *FT'|/FT'|ε
func termPlus(val float64) float64 {

	switch tok {
	case '*':
		lexNext()
		val *= factor()
		return termPlus(val)
	case '/':
		lexNext()
		val /= factor()
		return termPlus(val)
	default:
		return val
	}

	return val
}

//F -> NUMBER|(E)
func factor() float64 {

	switch tok {
	case scanner.Int:
		val, _ := strconv.ParseFloat(text, 64)
		lexNext()
		return val
	case scanner.Float:
		val, _ := strconv.ParseFloat(text, 64)
		lexNext()
		return val
	case '(':
		lexNext()
		val := expr()
		if tok != ')' {
			fmt.Println("error: miss )")
		}
		lexNext()
		return val
	default:
		return 0
	}
}
