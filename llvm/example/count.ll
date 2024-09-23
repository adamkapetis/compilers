@vars = private global [26 x i32] zeroinitializer
@nl = private constant [2 x i8] c"\0a\00"

declare void @writeInteger(i64)
declare void @writeString(i8*)

define i32 @main() {
entry:
    %ptrx = getelementptr inbounds[26 x i32], [26 x i32]* @vars, i32 0, i32 23
    store i32 0, i32* %ptrx
    br label %loop
loop:
    %iter = phi i32 [42, %entry], [%remaining, %body]
    %loop_cond = icmp sgt i32 %iter, 0
    br i1 %loop_cond, label %body, label %endfor 
body: 
    %remaining = sub i32  %iter, 1

    %x = load i32, i32* %ptrx
    %xplus = add i32 %x, 1
    store i32 %xplus, i32* %ptrx

    %ext = sext i32 %xplus to i64
    call void @writeInteger(i64 %ext)
    %nl = getelementptr inbounds [2 x i8], [2 x i8]* @nl, i32 0, i32 0
    call void @writeString(i8* %nl)
    br label %loop

endfor:
    ret i32 0
}