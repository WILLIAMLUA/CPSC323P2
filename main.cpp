# Define a class and constructor for the parsing table
class ParsingTable:
    def __init__(self):
        #Define the parsing table as a dictionary
        self.table = {
            'E': {'a': ['T', 'Q'], '(': ['T', 'Q']},
            'Q': {'+': ['+', 'T', 'Q'], '-': ['-', 'T', 'Q'], ')': ['ε'], '$': ['ε']},
            'T': {'a': ['F', 'R'], '(': ['F', 'R']},
            'R': {'+': ['ε'], '-': ['ε'], '*': ['*', 'F', 'R'], '/': ['/', 'F', 'R'], ')': ['ε'], '$': ['ε']},
            'F': {'a': ['a'], '(': ['(', 'E', ')']}
        }
        
   # Define a method for the parsing function
    def parse(self, input_str):
        # Initialize the stack with the start symbol and end-of-string symbol
        stack = ['$','E']
        # Initialize the input string index
        i = 0
        # Loop until the stack is empty
        # Parses the stack until it is empty or an error is encountered, given an input string and current index.
        while stack:  
            # Pop the top element off 
            top = stack.pop()
            # Check if the top element matches the current input character
            if top == input_str[i]:
                # If the top matches, print the input string, stack, and production rule used
                print(f"Input: {input_str[i+1:]} \nStack: {stack + ['$']}  Production Rule: match {top}")
                i += 1
            # If the top is a terminal and it does not correspond to the current input character, send an error.
            elif top in ('a', '+', '-', '*', '/', '(', ')', '$'):
                print(f"Input: {input_str[i:]} \nStack: {stack + ['$']}  Production Rule: error")
                return False
            # If the top is not a terminal symbol, apply a production rule to derive a new string of symbols.
            else:
                try:
                    # Retrieve the production rule associated with this non-terminal and input character.
                    production = self.table[top][input_str[i]]
                    # Print the input string, stack, and production rule used
                    print(f"Input: {input_str[i:]} \nStack: {stack + production[::-1] + ['$']}  Production Rule: {top} -> {''.join(production)}")
                    # Replace the non-terminal with variables from the production rule
                    for symbol in reversed(production):
                        if symbol != 'ε':
                            stack.append(symbol)
                except KeyError:
                    # If no production rule is found, send an error
                    print(f"Input: {input_str[i:]} \nStack: {stack + ['$']}  Production Rule: error")
                    return False
        # If no more symbols to process in the stack, then the input string is accepted.
        return True

# Prompt the user for input
input_str = input('Enter the input string: ')

# Create an instance of the parsing table class
table = ParsingTable()

# Call the parsing function with the input string and end-of-string marker.
if table.parse(input_str + '$'):
    print("String is accepted/ valid.")
else:
    print("String is not accepted/ In valid.")
