; Kernel number
KERNEL equ 0x80

; System call numbers
SYSCALL_EXIT equ 1
SYSCALL_READ equ 3
SYSCALL_WRITE equ 4
SYSCALL_OPEN equ 5
SYSCALL_CLOSE equ 6
SYSCALL_TIME equ 13

; read write type
READ_ONLY equ 0
WRITE_ONLY equ 1

; stdin and stdout
STDIN equ 0
STDOUT equ 1

; message
section	.data
	greet_msg db "                           Welcome to the game!!                             ", 0xa
	lgreet_msg equ $-greet_msg

	border_msg db " ==========================================================================", 0xa
	lborder_msg equ $-border_msg

	rule db "| Rules :                                                                  |", 0xa
	lrule equ $-rule 

	rule1 db "| 1. Guest a number from 0 to 9.                                           |", 0xa
	lrule1 equ $-rule1

	rule2 db "| 2. If you guess correctly, you will get a point. Otherwise, no.          |", 0xa
	lrule2 equ $-rule2
	
	rule3 db "| 3. You must guest 8 times and collect 4 or more point to win the game.   |", 0xa
	lrule3 equ $-rule3

	enter_msg db "Press enter to continue "
	lenter_msg equ $-enter_msg 

	menu_msg db "                                Main Menu                                ", 0xa
	lmenu_msg equ $-menu_msg

	choice_msg db "| Please enter your choice:                                                |", 0xa
	lchoice_msg equ $-choice_msg

	newgame_msg db "| 1. New Game                                                              |", 0xa
	lnewgame_msg equ $-newgame_msg

	loadgame_msg db "| 2. Load Game                                                             |", 0xa
	lloadgame_msg equ $-loadgame_msg

	savegame_msg db "| 3. Save Game                                                             |", 0xa
	lsavegame_msg equ $-savegame_msg        

	statusmenu_msg db "| 4. Status                                                                |", 0xa
	lstatusmenu_msg equ $-statusmenu_msg

	exitmenu_msg db "| 5. Exit                                                                  |", 0xa
	lexitmenu_msg equ $-exitmenu_msg

	continue_msg db "| Press c to continue |"
	lcontinue_msg equ $-continue_msg

	enter_input_msg db ">> "
	lenter_input_msg equ $-enter_input_msg
	
	guest_msg db "Enter your guess number (enter m for back to main menu): "
	lguest_msg equ $-guest_msg

	your_guess_msg db "Your guess number is: "
	lyour_guess_msg equ $-your_guess_msg

	comp_guest_msg db "Computer's guess number is: "
	lcomp_guest_msg equ $-comp_guest_msg

	correct_msg db "Your guess is correct! You get a point. "
	lcorrect_msg equ $-correct_msg

	incorrect_msg db "Unfortunately, your guess is incorrect!"
	lincorrect_msg equ $-incorrect_msg

	round_msg db "Round "
	lround_msg equ $-round_msg

	point_msg db "Point: "
	lpoint_msg equ $-point_msg

	win_msg db "Congratulations! You win the game!"
	lwin_msg equ $-win_msg

	lose_msg db "You lose the game! Don't Give up!"
	llose_msg equ $-lose_msg

	exit_msg db "Thank you for playing!", 0xa, 0xa
	lexit_msg equ $-exit_msg

	saved_msg db "Your progress have been saved!", 0xa
	lsaved_msg equ $-saved_msg

	load_msg db "Success loading progress!"
	lload_msg equ $-load_msg

	newline db 0xa

	invalid_msg db "Command invalid!", 0xa
	linvalid_msg equ $-invalid_msg 

	guest_invalid_msg db "Invalid input! Please enter a number from 0 to 9.", 0xa
	lguest_invalid_msg equ $-guest_invalid_msg

	filename db "save.txt", 0
	lfilename equ $-filename

	sperator db "-"

; variables
section .bss
	char: resb 1
	comp_guest: resd 1
	points: resd 1
	rounds: resd 1
	input: resd 1
	buff: resb 3
	file: resb 1

; program
section .text
	global _start

_start:
	mov ecx, greet_msg
	mov edx, lgreet_msg
	call write
	call newl
	
	call rules
	call press_enter

	mov dword [rounds], '0'
	mov dword [points], '0'
	mov byte [comp_guest], '1'

	call main_menu
	; main program
	main :
		call guesting

		cmp dword [input], 'm'
		je main_menu

		cmp dword [input], '9'
		ja invalid_guest

		call randint
		mov [comp_guest], eax

		call number_guest
		call compare
		call status

		cmp dword [rounds], '8'
		je end_game

		jmp main

; print a string
write:
	mov eax, SYSCALL_WRITE
	mov ebx, STDOUT
	int KERNEL

	ret

; print a newline
newl:
	mov eax, SYSCALL_WRITE
	mov ebx, STDOUT
	mov ecx, newline
	mov edx, 1
	int KERNEL
	ret

; print a border
border:
	mov ecx, border_msg
	mov edx, lborder_msg
	call write
	ret

; read an input
read:
	mov eax, SYSCALL_READ
	mov ebx, STDIN
	int KERNEL
	ret

; clear buffer
clear_input:
	mov ecx, input
	mov edx, 1
	call read

	ret

; exit program
exit:
	call clear_input

	mov ecx, exit_msg
	mov edx, lexit_msg
	call write

	mov eax, SYSCALL_EXIT
	xor ebx, ebx
	int KERNEL

; print rules
rules:
	call border

	mov ecx, rule
	mov edx, lrule
	call write

	mov ecx, rule1
	mov edx, lrule1
	call write

	mov ecx, rule2
	mov edx, lrule2
	call write

	mov ecx, rule3
	mov edx, lrule3
	call write

	call border

	call newl

	ret

; print a message and wait for user to press enter
press_enter:
	mov ecx, enter_msg
	mov edx, lenter_msg
	call write

	ret
; print main menu
main_menu:
	call clear_input

	call newl
	call newl
	mov ecx, menu_msg
	mov edx, lmenu_msg
	call write

	call border
	
	mov ecx, choice_msg
	mov edx, lchoice_msg
	call write
	
	mov ecx, newgame_msg
	mov edx, lnewgame_msg
	call write

	mov ecx, loadgame_msg
	mov edx, lloadgame_msg
	call write

	mov ecx, savegame_msg
	mov edx, lsavegame_msg
	call write

	mov ecx, statusmenu_msg
	mov edx, lstatusmenu_msg
	call write

	mov ecx, exitmenu_msg
	mov edx, lexitmenu_msg
	call write

	call border

	cmp dword [rounds], '1'
	jae l2

	jmp choice

; choices menu
choice:
	call input_menu

	cmp dword [input], '1'
	je reset

	cmp dword [input], '2'
	je load

	cmp dword [input], '3'
	je save

	cmp dword [input], '4'
	je write_status

	cmp dword [input], '5'
	je exit

	call invalid_command
	jmp main_menu
	
	ret
; print status
write_status:
	call status
	je main_menu
; alternatif menu
l2:
	mov ecx, continue_msg
	mov edx, lcontinue_msg
	call write

	call input_menu

	cmp dword [input], 'c'
	je main

	cmp dword [input], 'n'
	je main_menu

	jmp choice

	ret
; get input choices menu from user
input_menu:
	mov ecx, enter_input_msg
	mov edx, lenter_input_msg
	call write

	mov ecx, input
	mov edx, 1
	call read

	ret
; reset game
reset:
	mov dword [rounds], '0'
	mov dword [points], '0'
	je main
; invalid command
invalid_command:
	mov ecx, invalid_msg
	mov edx, linvalid_msg
	call write

	ret

invalid_guest:
	mov ecx, guest_invalid_msg
	mov edx, lguest_invalid_msg
	call write

	jmp main
; save game
save:
	mov eax, SYSCALL_OPEN
	mov ebx, filename
	mov ecx, WRITE_ONLY
	int KERNEL

	mov [file], eax

	mov ecx, points
	mov edx, 1
	call write_file

	mov ecx, sperator
	mov edx, 1
	call write_file

	mov ecx, rounds
	mov edx, 1
	call write_file

	call close_file

	call status
	call newl

	mov ecx, saved_msg
	mov edx, lsaved_msg
	call write

	jmp main_menu
; load game
load:
	mov eax, SYSCALL_OPEN
	mov ebx, filename
	mov ecx, READ_ONLY
	int KERNEL

	mov [file], eax

	
	mov eax, SYSCALL_READ
	mov ebx, [file]
	mov ecx, buff
	mov edx, 3
	int KERNEL

	xor eax, eax

	mov al, byte [buff]
	mov dword [points], eax
	mov al, byte [buff+2]
	mov dword [rounds], eax

	call close_file

	call status
	call newl

	mov ecx, load_msg
	mov edx, lload_msg
	call write

	jmp main
; write file
write_file:
	mov ebx, [file]
	mov eax, SYSCALL_WRITE
	int KERNEL

	ret
; close file
close_file:
	mov eax, SYSCALL_CLOSE
	mov ebx, [file]
	int KERNEL

	ret
; get guest number from user input
guesting:
	call clear_input
	
	call newl

	mov ecx, guest_msg
	mov edx, lguest_msg
	call write

	mov ecx, input
	mov edx, 1
	call read

	ret
; randomizer number
randint:
	mov ebx, char
	mov eax, SYSCALL_TIME
	int KERNEL

	mov eax, [ebx]
	mov ebx, 10
	div ebx
	add edx, '0'

	mov eax, edx

	ret
; print guest number
number_guest:
	call newl

	mov ecx, your_guess_msg
	mov edx, lyour_guess_msg
	call write

	mov ecx, input
	mov edx, 1
	call write

	call newl

	mov ecx, comp_guest_msg
	mov edx, lcomp_guest_msg
	call write

	mov ecx, comp_guest
	mov edx, 1
	call write

	call newl

	ret
; print status
status:
	call newl

	mov ecx, round_msg
	mov edx, lround_msg
	call write

	mov ecx, rounds
	mov edx, 1
	call write

	call newl

	mov ecx, point_msg
	mov edx, lpoint_msg
	call write

	mov ecx, points
	mov edx, 1
	call write

	call newl

	ret
; compare guest number with computer number
compare:
	push eax
	push ebx
	mov eax, dword [input]
	mov ebx, dword [comp_guest]

	cmp eax, ebx
	je correct

	jmp incorrect
; correct guess
correct:
	call newl

	mov ecx, correct_msg
	mov edx, lcorrect_msg
	call write

	call newl

	inc dword [points]
	inc dword [rounds]

	jmp l3
; incorrect guess
incorrect:
   call newl

   mov ecx, incorrect_msg
   mov edx, lincorrect_msg
   call write

   call newl

   inc dword [rounds]

   jmp l3
; return to main
l3:
   pop ebx
   pop eax
   ret
; reach end round
end_game:
	pop eax

	mov eax, dword [points]

	cmp eax, '4'
	jae win

	jmp lose
; win game
win:
	call newl

	mov ecx, win_msg
	mov edx, lwin_msg
	call write

	call newl

	call exit
; lose game
lose:
	call newl

	mov ecx, lose_msg
	mov edx, llose_msg
	call write

	call newl

	call exit
