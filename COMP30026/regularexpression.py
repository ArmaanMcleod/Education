# Testing expressions
expressions = ["a", "cc", "bbc", "cabcbbca", "acaacbacbb", "abcabcabc", 
               "caaa", "bbcaacbcaac"]

# Getting substrings
def get_substrings(string, sublen):
    substrs = []

    for i in range(len(string)):
        if len(string[i:i+sublen]) == sublen:
            substrs.append(string[i:i+sublen])

    return substrs

# extracting valid expressions
def get_valid_expression(expressions, minlen, char_to_check):

    valid = []

    for string in expressions:

        # if string is less than min length, then it is already valid
        if len(string) < minlen:
            valid.append(string)

        else:

            # get the subtrings
            lst = get_substrings(string, minlen)

            # Check if the substring contains exactly one of the characters
            if all(substring.count(char_to_check) == 1 for substring in lst):
                valid.append(string)

    return valid

print("Valid expressions with all substrings of length 3 containing exactly one c:")
print(get_valid_expression(expressions, 3, "c"))

^.{0,2}$|^[^c]{0,2}(c[^c]{2})*c[^c]{0,2}$

^[abc]{0,2}$|^[ab]{0,2}(c[ab]{2})*c[ab]{0,2}$