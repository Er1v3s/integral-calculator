;win_macros.inc

;macros:
; clrscr			 - wyczyœæ okno
; pob_znak			 - pobierz 1 znak ASCII bez echa (po wykonaniu makra znak znajduje siê w rejestrze AL)
; pob_znak_ECHO 		 - pobierz 1 znak ASCII z echem (po wykonaniu makra znak znajduje siê w rejestrze AL)
; ustaw_kursor wiersz, kolumna	 - ustaw kursor na pozycji 'wiersz','kolumna'
; wyswietl txt			 - wyœwietl zmienn¹ tekstow¹ o nazwie podanej jako argument
; wysw_znak znak_ASCII		 - wyœwietla 1 znak ASCII ze zmiennej podanej jako argument
; end_prog			 - koñczy program



;DEFINICJE MACRO

;-----------------------------------------------------------------------------------------------------
; DEFINICJE STRUKTUR
;-----------------------------------------------------------------------------------------------------
;Defines the coordinates of a character cell in a console screen buffer.
struct COORD
      X dw ?
      Y dw ?
ends

;Defines the coordinates of the upper left and lower right corners of a rectangle.
struct SMALL_RECT
       Left   dw     ?
       Top    dw     ?
       Right  dw     ?
       Bottom dw     ?
ends


;Contains information about a console screen buffer.
struct CONSOLE_SCREEN_BUFFER_INFO
       dwSize			COORD		?
       dwCursorPosition 	COORD		?
       wAttributes		dw		?
       srWindow 		SMALL_RECT	?
       dwMaximumWindowSize	COORD		?
ends

macro clrscr
{
  pushad
  invoke GetStdHandle, STD_OUTPUT_HANDLE
  mov [hCon],eax
  invoke GetConsoleScreenBufferInfo, [hCon], csbi
  mov ax, [csbi.dwSize.X]
  mul [csbi.dwSize.Y]
  mov [ConSize],eax
  invoke FillConsoleOutputCharacter, [hCon], ' ', [ConSize], [coordScreen], cCharsWritten
  invoke FillConsoleOutputAttribute, [hCon], dword[csbi.wAttributes] , [ConSize], [coordScreen], cCharsWritten
  invoke SetConsoleCursorPosition, [hCon], [coordScreen]
  popad
}

macro pob_znak
{
	pushad
	cinvoke getch
	mov [temp_eax], eax
	popad
	mov eax,[temp_eax]
}

macro pob_znak_ECHO
{
	pushad
	cinvoke getch
	mov [temp_eax], eax
	cinvoke putchar, eax
	popad
	mov eax,[temp_eax]
}

macro ustaw_kursor wiersz, kolumna
{
	pushad
	invoke GetStdHandle, STD_OUTPUT_HANDLE
	mov [hCon],eax
	mov ax,wiersz
	shl eax,16
	mov ax,kolumna
	invoke SetConsoleCursorPosition,[hCon],eax
	popad
}

macro wyswietl txt
{
       pushad
       cinvoke printf, txt
;	cinvoke puts, txt
       popad
}

macro wysw_znak znak_ASCII
{
	pushad
	mov al, znak_ASCII
	cbw
	cwde
	cinvoke putchar, eax
	popad
}

macro end_prog
{
       invoke ExitProcess
}



section '.data' data readable writeable
	coordScreen	      COORD				 0,0;	     // upper left corner
	cCharsWritten	      dd				 ?;
	ConSize 	      dd				 ?;
	hCon		      dd				 ?;
	csbi		      CONSOLE_SCREEN_BUFFER_INFO	 ?
	temp_eax	      dd				 ?


section '.idata' import data readable writeable
     library msvcrt,'MSVCRT.DLL',\
	     kernel32,'KERNEL32.DLL'

     import msvcrt,\
     getch,'_getch',\
     putchar,'putchar',\
     puts,'puts',\
     printf,'printf',\
     scanf,'scanf'

     import kernel32,\
     SetConsoleCursorPosition,'SetConsoleCursorPosition',\
     GetStdHandle,'GetStdHandle',\
     GetConsoleScreenBufferInfo,'GetConsoleScreenBufferInfo',\
     FillConsoleOutputCharacter,'FillConsoleOutputCharacterA',\
     FillConsoleOutputAttribute,'FillConsoleOutputAttribute',\
     ExitProcess,'ExitProcess'

