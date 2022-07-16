
# coding: utf-8

# In[ ]:


# CS220 - Programming Assignment 1 : Boolean Logic
# author - Asa Ben-Hur and Nirmal Prajapati

# NOTE:
# You must use small single letters for your variable names, for eg. a, b, c
# You may use parenthesis to group your expressions such as 'a and (b or c)'

# Implement the following four functions:
# truth_table, count_satisfying, is_tautology and are_equivalent

# Submission:
# Submit this file using the checkin system on the course web page.



######## Do not modify the following block of code ########
# ********************** BEGIN *******************************

from functools import partial
import re


class Infix(object):
    def __init__(self, func):
        self.func = func
    def __or__(self, other):
        return self.func(other)
    def __ror__(self, other):
        return Infix(partial(self.func, other))
    def __call__(self, v1, v2):
        return self.func(v1, v2)

@Infix
def implies(p, q) :
    return not p or q

@Infix
def iff(p, q) :
    return (p |implies| q) and (q |implies| p)


# You must use this function to extract variables
# This function takes an expression as input and returns a sorted list of variables
# Do NOT modify this function
def extract_variables(expression):
    sorted_variable_set = sorted(set(re.findall(r'\b[a-z]\b', expression)))
    return sorted_variable_set

# *********************** END ***************************



############## IMPLEMENT THE FOLLOWING FUNCTIONS  ##############
############## Do not modify function definitions ##############


# This function calculates a truth table for a given expression
# input: expression
# output: truth table as a list of lists
# You must use extract_variables function to generate the list of variables from expression
# return a list of lists for this function
def truth_table(expression):
    table = []
    variables = extract_variables(expression)
    size = len(variables)
    expr = expression
    table = truthtable(size)
    count = 0
    for list in table:
        for i in list:
#             print(count, "=",variables[count])
            exec(variables[count] + '=' + str(i))
            count += 1
            if count == size:
                list.append(eval(expr))
                break
#         list.append(eval(expr))
        count = 0
    return table

def truthtable (n):
    if n < 1:
        return [[]]
    truth = truthtable(n-1)
    return [row + [i] for row in truth for i in [True, False]]

# count the number of satisfying values
# input: expression
# output: number of satisfying values in the expression
def count_satisfying(expression):
    words = expression.split()
    count = 0
    for x in words:
        if x == 'and':
            count += 1
        if x == 'or':
            count += 1
        if x == 'not':
            count += 1
        if x == '(and':
            count += 1
        if x == '(or':
            count += 1
        if x == '(not':
            count += 1
        if x == 'and)':
            count += 1
        if x == 'or)':
            count += 1
        if x == 'not)':
            count += 1
        if x == '|implies|':
            count += 1
        if x == '|iff|':
            count += 1
        if x == '(|implies|':
            count += 1
        if x == '(|iff|':
            count += 1
        if x == '|implies|)':
            count += 1
        if x == '|iff|)':
            count += 1            
    return count

# if the expression is a tautology return True,
# False otherwise
# input: expression
# output: bool
def is_tautology(expression):
    table = truth_table(expression)
    for i in range(len(table)):
        for j in range(len(table[i])):
# truth = []
# expression = 'a and b'
# for a in [True, False]:
#     for b in [True, False]:
#         row = [a,b, eval(expression)]
#         truth.append(row)
# print(truth))):
            if table[i][-1] == False:
                return False
    return True

# if expr1 is equivalent to expr2 return True,
# False otherwise
# input: expression 1 and expression 2
# output: bool
def are_equivalent(expr1, expr2):
#     if eval(expr1) == True and eval(expr2) == True:
#         list1 = extract_variables(expr1)
#         list2 = extract_variables(expr2)
#         if ((len(list1) == len(list2)) and (all(i in list2 for i in list1))):
#             return True
#     if eval(expr1) == False and eval(expr2) == False:
#         list1 = extract_variables(expr1)
#         list2 = extract_variables(expr2)
#         if ((len(list1) == len(list2)) and (all(i in list2 for i in list1))):
#             return True
#     return False
    list1 = extract_variables(expr1)
    list2 = extract_variables(expr2)
    if ((len(list1) == len(list2)) and (all(i in list2 for i in list1))):
        table1 = truth_table(expr1)
        table2 = truth_table(expr2)
        value1 =[]
        value2 =[]
        for i in range(len(table1)):
            for j in range(len(table1[i])):
                value1.append(table1[i][-1])
        for i in range(len(table2)):
            for j in range(len(table2[i])):
                value2.append(table2[i][-1])
        if value1 == value2:
            return True
    return False

