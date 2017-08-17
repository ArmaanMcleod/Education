data BoolExpr
= BoolConst Bool
| BoolOp BoolOp BoolExpr BoolExpr
| CompOp CompOp IntExpr IntExpr

data IntExpr
= IntConst Int
| IntOp IntOp IntExpr IntExpr
| IntIfThenElse BoolExpr IntExpr IntExpr

data BoolOp  = And
data CompOp = LessThan
data IntOp = Plus | Times

boolVal :: BoolExpr -> Bool
boolVal (BoolConst b) = b
boolVal (BoolOp And x y) = boolVal x && boolVal y
boolVal (CompOp LessThan x y) = intVal x < intVal y

intVal :: IntExpr -> Int
intVal (IntConst i) = i
intVal (IntOp Plus x y) = intVal x + intVal y
intVal (IntOp Times x y) = intVal x * intVal y

intVal (IntIfThenElse b t e) = 
	if boolVal b 
	then intVal t
	else intVal e