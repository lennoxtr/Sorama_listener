#line 1 "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/mpg123/src/-66150af195.clean/ports/cmake/src/libmpg123/../../../../src/libmpg123/getcpuflags_x86_64.S"








#line 1 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"












#line 1 "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/mpg123/x64-windows-rel/src\\config.h"






































































































































































#line 168 "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/mpg123/x64-windows-rel/src\\config.h"









#line 14 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"



#line 21 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"





#line 27 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"











































#line 71 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"







#line 79 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"


#line 83 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"


#line 86 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"




























































#line 147 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"



#line 151 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"

#line 153 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"





#line 159 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"






#line 166 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"









#line 176 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"

#line 178 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"



#line 182 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"








#line 191 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"









#line 201 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"

#line 203 "C:\\Users\\huykh\\source\\repos\\Test_sorama\\vcpkg_installed\\x64-windows\\vcpkg\\blds\\mpg123\\src\\-66150af195.clean\\src\\libmpg123\\mangle.h"

#line 10 "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/mpg123/src/-66150af195.clean/ports/cmake/src/libmpg123/../../../../src/libmpg123/getcpuflags_x86_64.S"

	.text
	.balign 4
	.globl INT123_getcpuflags
INT123_getcpuflags:
	push	%rbp
	mov		%rsp, %rbp
	push	%rbx
	

	push	%rdi
	mov		%rcx, %rdi
#line 23 "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/mpg123/src/-66150af195.clean/ports/cmake/src/libmpg123/../../../../src/libmpg123/getcpuflags_x86_64.S"

	movl	$0, 12(%rdi)
	movl	$0, 16(%rdi)

	mov		$0x80000000, %eax
	cpuid
	cmp		$0x80000001, %eax
	jb		1f
	mov		$0x80000001, %eax
	cpuid
	movl	%edx, 12(%rdi)
1:
	mov		$0x00000001, %eax
	cpuid
	movl	%eax, (%rdi)
	movl	%ecx, 4(%rdi)
	movl	%edx, 8(%rdi)
	test	$0x04000000, %ecx
	jz		2f
	test	$0x08000000, %ecx
	jz		2f
	xor		%ecx, %ecx
	.byte	0x0f, 0x01, 0xd0 
	movl	%eax, 16(%rdi)
	movl	(%rdi), %eax
2:

	pop		%rdi
#line 52 "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/mpg123/src/-66150af195.clean/ports/cmake/src/libmpg123/../../../../src/libmpg123/getcpuflags_x86_64.S"
	pop		%rbx
	mov		%rbp, %rsp
	pop		%rbp
	ret
	

