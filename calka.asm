format PE Console 4.0

entry start

include 'win32ax.inc'
include 'win_macros.inc'

section '.code' code readable executable

start:
	cinvoke printf, <"Wprowadz a: ">
	ustaw_kursor 0,12
	cinvoke scanf, <"%lf">, a

	ustaw_kursor 1,0
	cinvoke printf, <"Wprowadz b: ">
	ustaw_kursor 1,12
	cinvoke scanf, <"%lf">, b

	ustaw_kursor 2,0
	cinvoke printf, <"Wprowadz n: ">
	ustaw_kursor 2,12
	cinvoke scanf, <"%lf">, n


	finit
	fld [b]   ; 3
	fld [a]   ; 1
	fst [temp]   ; 1
	fsubp
	fld [n]
	fist [n_calkowite]
	fdivp
	fstp [var_dx]

	finit
	fldz
	fstp [result]

	xor	ecx,ecx
	mov	cx,[n_calkowite]
	sub	cx,1

for_loop:
	mov	[n_calkowite], cx

	;
	fld	[var_dx]
	fild	[n_calkowite]
	fmulp
	fld	[a]
	faddp

	;cos(3 *(a + n_calkowite * var_dx))
	fild	[const3]
	fmulp
	fcos

	; 2 * (cos(3 *(a + n_calkowite * var_dx))
	fild	[const2]
	fmulp

	;result += 2 * (cos(3 *(a + n_calkowite * var_dx))
	fld	[result]
	faddp
	fstp	[result]

	loop	for_loop

	;(var_dx / 2)
	fld	 [var_dx]
	fild	 [const2]
	fdivp
	fstp	 [x_i]

	;cos(3*a)
	fild	[const3]
	fld	[a]
	fmulp
	fcos

	;(2 * cos(3 * a))
	fild	[const2]
	fmulp
	fstp	[y_i]

	;cos(3 * b)
	fild	[const3]
	fld    [b]
	fmulp
	fcos

	;(2 * cos(3 * b))
	fild	[const2]
	fmulp
	fld	[y_i]
	faddp
	fstp	[y_i]

	;2 * result
	fild	[const2]
	fld	[result]
	fmulp

	;(2 * cos(3 * a) + 2 * result)
	fld	[y_i]
	faddp

	;(var_dx /2) * (2 * cos(3 * a) + 2 * result)
	fld	[x_i]
	fmulp
	fstp	[final_result]

	ustaw_kursor 4,0
	cinvoke printf, <'Wynik: %.3lf ',0>, dword [final_result], dword [final_result+4]

	pob_znak
	end_prog


section '.data' readable writeable
	a dq 0
	b dq 0
	n dq 0
	n_calkowite dw 0
	var_dx dq 0
	temp dq 0
	result dq 0
	final_result dq 0
	x_i dq 0;
	y_i dq 0;
	const2 dw 2
	const3 dw 3