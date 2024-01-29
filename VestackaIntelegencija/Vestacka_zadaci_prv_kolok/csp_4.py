from constraint import *
def check_same(s1,s2):
    return s1!=s2
def check_kocka(rows,columns):
    if rows in range(0,3):
        if columns in range(0,3):
            return 1
        elif columns in range(3,6):
            return 2
        elif columns in range(6,9):
            return 3
    elif rows in range(3,6):
        if columns in range(0,3):
            return 4
        elif columns in range(3,6):
            return 5
        elif columns in range(6,9):
            return 6
    elif rows in range(6,9):
        if columns in range(0,3):
            return 7
        elif columns in range(3,6):
            return 8
        elif columns in range(6,9):
            return 9
if __name__ == '__main__':
    x=input()
    if(x=="BacktrackingSolver"):
        problem = Problem(BacktrackingSolver())
    elif(x=="RecursiveBacktrackingSolver"):
        problem=Problem(RecursiveBacktrackingSolver())
    else:
        problem=Problem(MinConflictsSolver())

    variables=range(0,81)
    domain=range(1,10)
    problem.addVariables(variables,domain)
    for i in range(0,81):
        for j in range(0,81):
            if(i<j):
                if(i//9==j//9):
                    problem.addConstraint(check_same,(i,j))
                if(i%9==j%9):
                    problem.addConstraint(check_same,(i,j))
                cube_i=check_kocka(i%9,i//9)
                cube_j=check_kocka(j%9,j//9)
                if(cube_i==cube_j):
                    problem.addConstraint(check_same,(i,j))




    # ---Tuka dodadete gi ogranichuvanjata----------------

    # ----------------------------------------------------

    print(problem.getSolution())
