
;a hello-world asm program using the c++ printf() function
;to provide output


 ; this instruction tells MASM to be case sensitive otherwise makes everything uppercase
option casemap:none

;read/write data variable section
.data       

;The "10" value is a newline feed character in "c++" 
fmtStr db   "Hello,Revirus!", 10 , 0     

; directive for start of code instruction section
.code

;declaring the name of external function being called
;this helps MASM know that printf is an external c++ function

 externdef printf:proc

 public asmFunc
 asmFunc proc
 ;stack alignement for printf function to be called
 ; stack alignement should follow N MODULO 16 = 8 rule just after entry into called  procedure as return address pushed
 ; 32 bytes of shadow stack space to be created for MS x64 function abi 
 ; 32 bytes needs to reserved even if number of arguments less than four (rcx,rdx,r8,r9)
 ; 8 bytes for return address to be used when function returns back 
 ; now total 40 bytes , but stak alignement needs to follow N MODULO 16 = 8 rule
 ;40 modulo 16 = 8 

 sub rsp,56 ; this should be greater than  32 to work, why 56 needs to find out
 lea rcx,fmtStr

 call printf

 add rsp,56

 ret ; returns to the caller

 asmFunc endp
 end


