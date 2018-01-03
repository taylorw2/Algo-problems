// Expression type
type Expression =
    | X
    | Y
    | Const of float
    | Neg of Expression
    | Add of Expression * Expression
    | Sub of Expression * Expression
    | Mul of Expression * Expression

// exprToString formatting function    
let exprToString expr =
    let rec recExprStr parens expr =
        let lParen = if parens then "(" else ""
        let rParen = if parens then ")" else ""
        match expr with
        | X -> "x"
        | Y -> "y"
        | Const(n) -> n.ToString()
        | Neg(e) -> lParen + "-" + recExprStr true e + rParen
        | Add(e1, e2) -> lParen + recExprStr true e1 + "+" + recExprStr true e2 + rParen
        | Sub(e1, e2) -> lParen + recExprStr true e1 + "-" + recExprStr true e2 + rParen
        | Mul(e1, e2) -> lParen + recExprStr true e1 + "*" + recExprStr true e2 + rParen
    recExprStr false expr

// TODO: write simplify function
let rec simplify expr =
    match expr with 
    |X -> X
    |Y -> Y
    |Const(n) -> Const(n)
    |Add(X, Const(r)) -> if r = float 0 then X
                         else Add(X, Const(r))
    |Add(Const(r),X) -> if r = float 0 then X
                        else Add(X, Const(r))
    |Add(Y, Const(r)) -> if r = float 0 then Y
                         else Add(Y, Const(r))
    |Add(Const(r),Y) -> if r = float 0 then Y 
                        else Add(Y, Const(r))
    |Add(Const(l),Const(r)) -> Const(l + r)
    |Add(e1, e2) -> if simplify(e1) = X && simplify(e2) = X then Add(simplify(e1), simplify(e2))
                    elif simplify(e1) = Y && simplify(e2) = X then Add(simplify(e1), simplify(e2))
                    elif simplify(e1) = X && simplify(e2) = Y then Add(simplify(e1), simplify(e2))
                    elif simplify(e1) = Y && simplify(e2) = Y then Add(simplify(e1), simplify(e2))
                    elif simplify(e1) = e1 && simplify(e2) = e2 then Add(simplify(e1), simplify(e2))
                    else simplify(Add(simplify(e1),simplify(e2)))
    |Sub(X, Const(r)) -> if r = float 0 then X
                         else Sub(X, Const(r))
    //|Sub(Y,Y) -> Const(float 0)
   // |Sub(X,X) -> Const(float 0)
    |Sub(Const(r),X) -> if r = float 0 then Neg(X)
                        else Sub(Const(r),X)
    |Sub(Y, Const(r)) -> if r = float 0 then  Y
                         else Sub(Y, Const(r))
    |Sub(Const(r),Y) -> if r = float 0 then Neg(Y)
                        else Sub(Const(r),Y)
    |Sub(Const(l),Const(r)) -> Const( l-r)
    |Sub(Const(r),e1) -> if r = 0.0 then simplify(Neg(simplify(e1)))
                         else Sub(Const(r),simplify(e1))
    |Sub(e1,Const(r)) -> if r = 0.0 then simplify(e1)
                         else Sub(simplify(e1),Const(r))
    |Sub(e1, e2) -> if simplify(e1) = simplify(e2) then Const(0.0)
                    //elif simplify(e1) = Y && simplify(e2) = X then Sub(simplify(e1), simplify(e2))
                    //elif simplify(e1) = X && simplify(e2) = Y then Sub(simplify(e1), simplify(e2))
                    //elif simplify(e1) = Y && simplify(e2) = Y then Const(0.0)
                    //elif simplify(e1) = X && simplify(e2) = X then Const(0.0)
                    //elif simplify(e1) = X then Sub(X, simplify(e2))
                    //elif simplify(e1) = Y then Sub(Y, simplify(e2))
                    //elif simplify(e2) = X then Sub(simplify(e1), X)
                    //elif simplify(e2) = Y then Sub(Y, simplify(e2))
                    elif simplify(e1) = e1 && simplify(e2) = e2 then Sub(simplify(e1), simplify(e2))
                    else simplify(Sub(simplify(e1),simplify(e2)))
    |Mul(X, Const(r)) -> if r = float 1 then X
                         elif r = float 0 then Const(float 0)
                         else Mul(Const(r),X)
    |Mul(Const(r),X) -> if r = float 1 then X
                        elif r = float 0 then Const(float 0)
                        else Mul(Const(r),X)
    |Mul(Const(r),Y) -> if r = float 1 then Y
                        elif r = float 0 then Const(float 0)
                        else Mul(Const(r),Y)
    |Mul(Y, Const(r))-> if r = float 1 then Y
                        elif r = float 0 then Const(float 0)
                        else Mul(Const(r),Y)
    |Mul(Const(l), Const(r)) -> Const(r*l)
    |Mul(e1, e2) ->  if simplify(e1) = e1 && simplify(e2) = e2 then Mul(simplify(e1), simplify(e2))
                     else simplify(Mul(simplify(e1),simplify(e2)))
    |Neg(Const(l)) -> Const(l * float -1)

    |Neg(X) -> Neg(simplify(X))
    |Neg(Y) -> Neg(simplify(Y))
    |Neg(Add(X,X)) -> Add(Neg(X),Neg(X))
    |Neg(e) -> if simplify(e) = Neg(X) then X
               elif simplify(e) = Neg(Y) then Y
               else simplify(Neg(simplify(e)))

         

// Tests
printfn "---Provided Tests---"
let t1 = Add(Const 5.0, Const 3.0)
let t2 = Sub(Const 5.0, Const 3.0)
let t3 = Mul(Const 5.0, Const 3.0)
let t4 = Neg(Const 4.0)
let t5 = Neg(Const -9.0)
let t6 = Add(X, Const 0.0)
let t7 = Add(Const 0.0, Y)
let t8 = Sub(X, Const 0.0)
let t9 = Sub(Const 0.0, Y)
let t10 = Sub(Y, Y)
let t11 = Mul(X, Const 0.0)
let t12 = Mul(Const 0.0, Y)
let t13 = Mul(X, Const 1.0)
let t14 = Mul(Const 1.0, Y)
let t15 = Neg(Neg X)
let t16 = Sub(Mul(Const 1.0, X), Add(X, Const 0.0))
let t17 = Add(Mul(Const 4.0, Const 3.0), Sub(Const 11.0, Const 5.0))
let t18 = Sub(Sub(Add(X, Const 1.0), Add (X, Const 1.0)), Add(Y, X))
let t19 = Sub(Const 0.0, Neg(Mul(Const 1.0, X)))
let t20 = Mul(Add(X, Const 1.0), Neg(Sub(Mul(Const 2.0, Y), X)))
let t21 = Add(Add(Sub(X, Const 1.0), Sub (X, Const 1.0)), Sub(Y, X))
let t22 = Sub(Mul(Const 4.0, Const 3.0), Add(Const 11.0, Const 5.0))
let t23 = Add(Add(X, Const 1.0), Neg(Sub(Mul(Const 2.0, Y), X)))   
let t24 = Sub(Add(X, Const 1.0), Neg(Sub(Mul(Const 2.0, Y), X)))    
let t25 = Neg(Neg(Neg(Neg(Neg(Const(5.0))))))
let t26 = Mul( Sub(X,X) , (Mul(Const(5.0), (Add(Const(3.0), Const(2.0)) ))))
let t27 = Mul(Sub(X,X), Const 1.0)
let t28 = Mul((Sub(Y,Y)) , (Mul(Const(5.0), (Add(Const(3.0), Const(2.0))))))
let t29 = Add(Const(3.0), Mul(Const(2.0), Mul(Const(5.0), Const(5.0))))
let t30 = Mul(Add(Const(2.0), Const(0.0)) , Mul(Const(2.0), Mul(Const(5.0), Const(5.0))))
let t31 = Mul(Const(2.0), (Mul(Const(2.0), (Mul(Const(2.0), (Add(Const(2.0), (Mul(Const(5.0),Const(5.0))) )) )) )) )
let t32 = Mul(Const(2.0), (Add(Const(2.0), (Mul(Const(5.0), Const(5.0))))))
let t33 = Mul(Const(2.0), Mul(Const(2.0), (Mul(Const(5.0), Const(5.0)))))
let t34 = Add(Mul(Neg(Const(3.0)), Sub(Mul(Const(5.0), Add(Const (2.0), Const(6.0))) , Const(0.0)) ), Const(120.0))
let t35 = Add(Const(5.0), Add(Const(5.0), Add(Const(5.0), Add(Const(5.0), Add(Const(5.0), Add(Const(5.0), Add(Const(5.0), Add(Const(5.0), Add(Const(5.0), Add(Const(5.0), Const(5.0))))))))))) 
let t36 = Mul(Const(5.0), Mul(Const(5.0), Mul(Const(5.0), Mul(Const(5.0), Mul(Const(5.0), Mul(Const(5.0), Add(Const(5.0), Mul(Const(5.0), Mul(Const(5.0), Add(Const(5.0), Add(Const(5.0), Add(Const(5.0), Add(Const(5.0), Const(5.0))))))))))))))




printfn "t1  Correct: 8\t\tActual: %s" (exprToString (simplify t1))
printfn "t2  Correct: 2\t\tActual: %s" (exprToString (simplify t2)) 
printfn "t3  Correct: 15\t\tActual: %s" (exprToString (simplify t3))
printfn "t4  Correct: -4\t\tActual: %s" (exprToString (simplify t4))
printfn "t5  Correct: 9\t\tActual: %s" (exprToString (simplify t5))
printfn "t6  Correct: x\t\tActual: %s" (exprToString (simplify t6))
printfn "t7  Correct: y\t\tActual: %s" (exprToString (simplify t7))
printfn "t8  Correct: x\t\tActual: %s" (exprToString (simplify t8))
printfn "t9  Correct: -y\t\tActual: %s" (exprToString (simplify t9))
printfn "t10 Correct: 0\t\tActual: %s" (exprToString (simplify t10))
printfn "t11 Correct: 0\t\tActual: %s" (exprToString (simplify t11))
printfn "t12 Correct: 0\t\tActual: %s" (exprToString (simplify t12))
printfn "t13 Correct: x\t\tActual: %s" (exprToString (simplify t13))
printfn "t14 Correct: y\t\tActual: %s" (exprToString (simplify t14))
printfn "t15 Correct: x\t\tActual: %s" (exprToString (simplify t15))
printfn "t16 Correct: 0\t\tActual: %s" (exprToString (simplify t16))
printfn "t17 Correct: 18\t\tActual: %s" (exprToString (simplify t17)) 
printfn "t18 Correct: -(y+x)\tActual: %s" (exprToString (simplify t18))
printfn "t19 Correct: x\t\tActual: %s" (exprToString (simplify t19))
printfn "t20 Correct: (x+1)*(-((2*y)-x))"
printfn "    Actual:  %s" (exprToString (simplify t20))
printfn "t21 Correct: (x-1)+(x-1)+(y-x)\tActual: %s" (exprToString (simplify t21))
printfn "t22 Correct: -4\tActual: %s" (exprToString (simplify t22))
printfn "t23 Correct: (x+1)+(-((2*y)-x))"
printfn "    Actual:  %s" (exprToString (simplify t23))
printfn ""
printfn "t24 Correct: (x+1)-(-((2*y)-x))"
printfn "    Actual:  %s" (exprToString (simplify t24))
printfn ""
printfn "t25  Correct: -5\t\tActual: %s" (exprToString (simplify t25))
printfn "t26  Correct: 0\t\tActual: %s" (exprToString (simplify t26))
printfn "t27  Correct: 0\t\tActual: %s" (exprToString (simplify t27))
printfn "t28  Correct: 0\t\tActual: %s" (exprToString (simplify t28))
printfn "t29  Correct: 53\t\tActual: %s" (exprToString (simplify t29))
printfn "t30  Correct: 100\t\tActual: %s" (exprToString (simplify t30))
printfn "t31  Correct: 216\t\tActual: %s" (exprToString (simplify t31))
printfn "t32  Correct: 54\t\tActual: %s" (exprToString (simplify t32))
printfn "t33  Correct: 100\t\tActual: %s" (exprToString (simplify t33))
printfn "t34  Correct: 0\t\tActual: %s" (exprToString (simplify t34))
printfn "t35  Correct: 55\t\tActual: %s" (exprToString (simplify t35))
printfn "t36  Correct: 9843750\t\tActual: %s" (exprToString (simplify t36))

System.Console.ReadKey() |> ignore


