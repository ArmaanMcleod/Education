def brute_prime(seed):
    """
    Takes a non-negative integer arguement seed from 2 to sqrt(n).
    Returns integer value of the lowest prime number >= seed.

    brute_prime(number) -> integer > 0
    """
    min_num = 2
    prime = None

    if seed == 0 or seed == 1:
        return min_num

    while min_num <= seed:
        prime = True
        
        for i in range(min_num, seed): # valid primes

            if seed % i == 0: 
                prime = False

        if not prime: 
            seed += 1
            
        else:
            return seed

def euclid_gcd(m, n):
    """
    Takes two non-negative integer arguements, m and n. Returns
    the integer value of their greatest common divisor.

    euclid_gcd(integer, integer) -> integer > 0
    """
    if n == 0:
        return m
    
    else:
        remainder = m % n
        return euclid_gcd(n, remainder)
    
def txt2num(txt, k=3):
    """
    Takes two arguements, a string and an integer, k, which specifies
    the number of digits each character should translate to, defaulting
    to 3. Returns an integer representation of txt.

    txt2num(string, integer) -> integer > 0
    """
    result = ""
   
    for i in range(len(txt)):
        integer_str = ord(txt[i])

        count = 0
        for x in str(integer_str):

            if x.isdigit():

                count += 1

        if count > 1:
            result += "{:0>{k}}".format(str(integer_str), k=k)
            
        else:
            result += str(integer_str)
 
    return int(result)


def num2txt(num, k=3):
    """
    Takes two arguements, a posive integer, and an integer, k, which
    specifies the number of digits each character should translate to,
    defaulting to 3. Returns a string representation of num.

    num2txt(integer, integer) -> string
    """
    result = ""
    
    str_list = []
    while num:

        #Translates last three digits into string
        last_three_digits = str(num)[-3:]
        ascii_str = chr(int(last_three_digits))
        str_list.append(ascii_str)

        #Continues process
        num //= 10**k  

    result += "".join([str(i) for i in str_list])

    return result[::-1]

def rsa(min_p, min_q, min_e):
    """
    Takes in three positive integer arguements. Returns a 3-tuple
    corresponding to the public key, private key and modulus.

    rsa(integer, integer, integer) -> tuple<int, int, int>
    """

    p = brute_prime(min_p)
    q = brute_prime(min_q)
    
    n = p * q
    phi = (p-1) * (q-1)
    
    e = brute_prime(min_e)

    while True:
        
        if euclid_gcd(e, phi) == 1:
            break
        
        else:
            e += 1

    d = extended_euclid(e, phi)

    return (d, e, n)

def rsa_encrypt(msg, e, n, k=3):
    """
    Takes in four arguements. An encrypted string msg, a positive integer e
    representing the public key, another positive integer n representing the
    modulus, and an optional k(default = 3) arguement, which defines the size 
    used to translate msg into an integer. Returns a positive integer containing
    the encrypted message.

    rsa_encrypt(string, integer, integer, integer) -> integer > 0
    """
    msg = txt2num(msg, k)
    encrypt = (msg **e) % n
    return encrypt


def rsa_decrypt(c, d, n, k=3):
    """
    Takes in four arguements. A positive integer c containing the encrypted
    message, a positve integer d representing the private key, a positive
    integer representing the modulus, and an option arguement k(default = 3)
    arguement, which defines the size used to translate the decrypted message back
    into a stirng. Returns a strng containing the decrypted message.

    rsa_decrypt(integer, integer, integer, integer) -> string
    """
    decrypt = (c **d) % n
    return num2txt(decrypt, k)
    

    
    

    

    

    
    
    


   

    

    

    

        

    
    
        
        

        


            





