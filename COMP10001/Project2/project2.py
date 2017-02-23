import csv
import string
from collections import defaultdict

set_graphemes = set(string.ascii_lowercase + "_")

def get_stats(train_file, valid_pfile="cmu-phonemes.txt", 
              valid_graphemes=set_graphemes):
    """
    Takes in three arguements. A csv file, train_file, which reads the
    alignment data in a csv format specifier. An optional csv file, valid_pfile,
    which reads the valid phoneme data. An optional arguement, valid_graphemes,
    which is collected in a set data structure, containing the full inventory
    of valid graphemes, including underscore.

    Returns 4-tuple of numbers based on the composition of the grapheme-phoneme
    sequences in the train_file. The first value contains the number of invalid
    rows in the train_file, where number of elements between both the grapheme-
    phoneme seqeunces. The second value illustrates the average number of
    phonemes per word, as a float. The third value is the average number of
    graphemes per word, not including null graphemes, which is also shown as a
    float. The final value contains the proportion of grapheme sequences
    containing one or more underscores, also enscribed as a float. The last
    three values are only based on valid rows. If a row is invalid, and the
    denominator is zero, then they must be returned to None.

    get_stats(string, string, set) -> tuple<int, float, float, float>

    or

    get_stats(string, string, set) -> tuple<int, None, None, None>
    """

    # reads alignment data
    csv_file = open(train_file)
    reader = csv.reader(csv_file)
    next(reader)
    
    phonemes_dict = open(valid_pfile)
    phonemes_read = csv.reader(phonemes_dict)
    
    # stores data in callable lists
    train_list = [list(x) for x in reader]
    valid_phonemes = ["".join(x) for x in phonemes_read]
    
    valid_rows = []
    invalid_rows = 0

    # flag check for valid rows
    flag = None

    # loops over alignment data
    for row in train_list: 
        flag = True

        # compares lengths in terms of whitespace
        if len(row[0].split()) == len(row[1].split()):
            flag = True

        else:
            continue

        # checks validity of phonemes and graphemes
        for elem in row[0].split():
            
            if elem not in valid_phonemes:
                flag = False
                        
        for char in row[1].split():
            
            for item in char:
                
                if item not in valid_graphemes: 
                    flag = False
                
        if not flag:
            continue
            
        valid_rows.append(row)

    # initialize result counts
    phoneme_count = 0
    grapheme_count = 0
    null_count = 0
    word_count = 0
    underscore = "_"

    # loops over valid rows to extract necessary data
    for i in range(len(valid_rows)):
        
        if valid_rows[i]:
            word_count += 1
            
            for x in valid_rows[i][1]:
                
                if x == underscore: 
                    null_count += 1

            phonemes = valid_rows[i][0].split()
            graphemes = valid_rows[i][1].split()
            
            for i in range(len(phonemes)):
                
                if str(phonemes[i]):
                    phoneme_count += 1

            # checks for grapheme underscores
            for i in range(len(graphemes)):
                
                for element in graphemes[i]:
                    
                    if element != underscore:
                        grapheme_count += 1

    # possible invalids rows available                    
    invalid_rows = len(train_list) - len(valid_rows)

    # checks for zero word count
    if not word_count:
        result = (invalid_rows, None, None, None)

    else:
        average_phonemes = phoneme_count/word_count
        average_graphemes = grapheme_count/word_count
        grapheme_proportion = null_count/word_count

        result = (invalid_rows, average_phonemes, average_graphemes,
                  grapheme_proportion)
        
    csv_file.close()
    phonemes_dict.close()
                        
    return result


def train_ngrams(train_file):
    """
    Takes in a single csv file arguement, train_file, which reads in the
    alignment data. Returns a 2-tuple containing the bigrams and trigrams.

    Bigrams is a default dictionary of dictionaries for a given phoneme, the
    key of the outer dictionary, and a given grapheme, the key for the inner
    dictionary. Trigrams is almost identical to Bigrams, except the key is in
    (phoneme, grapheme) context. inner values of the dictionaries correspond
    to the frequencies, stored as integers.

    train_ngrams(string) -> (defaultdict, defaultdict)
    """

    bigrams = defaultdict(dict)
    trigrams = defaultdict(dict)

    # reads alignment data
    csv_file = open(train_file)
    csv_reader = csv.reader(csv_file)
    next(csv_reader)

    # loops over alignment data
    for row in csv_reader:
        
        phonemes = row[0].split()
        graphemes = row[1].split()

        # first grapheme context
        special_symbol = list("^")

        relevant_graphemes = len(graphemes) - 1

        graphemes_list = graphemes[:relevant_graphemes]

        # Concatenate possible graphemes
        special_graphemes = special_symbol + graphemes_list

        for i in range(len(phonemes)):

            # sets occuring variables with respect to phonemes size
            phoneme = phonemes[i]
            grapheme = graphemes[i]
            new_grapheme = special_graphemes[i]
            tup = phoneme, new_grapheme

            # updates default dicts with frequencies
            bigrams[phoneme][grapheme] = bigrams[phoneme].get(grapheme, 0) + 1
            trigrams[tup][grapheme] = trigrams[tup].get(grapheme, 0) + 1
            
    csv_file.close()
            
    return (bigrams, trigrams)

            
def normalise(ngrams):
    """
    Takes in single arguement, ngrams, a default dictionary, in the form
    returned by train_ngram, for each bigrams and trigrams in the return
    tuple. Returns None, but converts each of the frequencies to
    probabilities.

    normalise(ngrams) -> Nonetype
    """
    
    for key1, value in ngrams.items():

        sums = 0
        for val in value.values():
            sums += val

        # replaces frequences with probabilities
        for key2 in value:
            ngrams[key1][key2] = value[key2]/sums
       
    return None
    

def speech2text(phonemes, bigrams, trigrams, alpha=1.0, topn=10):
    """
    Takes in four arguements. A string sequence, phoneme. A default
    dictionary of dictionaries of floats,bigrams, containing the bigram
    alignment probabilities. Another default dictionary of dictionaries
    as floats, containing the trigram alignment probabilities. A float,
    alpha, set to default value of 1.0 for the probabilities calculations.
    A final integer, topn, whiich sets the size of the beam for the
    probabilities calculations, set to 10 by default.

    Returns a list of two tuples, each containing the grapheme sequence in
    the form of a string, and probabililty of that sequence in float form.
    It is sorted in descending order of probability, sub-sorted
    orthographically in case of any ties that may occur.

    speech2text(string, {{}}, {{}}, float, int) -> list[tuple<list, float>]
    """
    
    phonemes_list = phonemes.split()

    beam = [(["^"], 1.0)]

    for phoneme in phonemes_list:

        # new beams after each iteration
        new_beams = []

        # loops over current grapheme in beam
        for current in beam:
            
            prev_grapheme = tuple(current[0])[-1]

            probability = current[1]

            # finds grapheme canditates in bigrams dictionary
            for grapheme in bigrams[phoneme]:

                bigram_prb = bigrams[phoneme][grapheme]

                # exception handing of keys in trigram probabilities    
                try:
                    trigram_prb = trigrams[(phoneme, prev_grapheme)][grapheme]
                    
                except:
                    trigram_prb = 0

                # overall probability calculation    
                prb = probability *((alpha*bigram_prb)+((1-alpha)*trigram_prb))

                if prb:
                    new_beams.append((current[0] + [grapheme], prb))
                    
                else:  
                    new_beams.append((current[0] + [grapheme], probability))

        # resets beam after each iteration
        beam = new_beams

        # prepares values for sorting
        new_list = []
        for key, value in beam:
            new_list.append((value*(-1), key))

        # sorts values with respect to highest scores
        result = []
        for key, value in sorted(new_list)[:topn]:
            result.append((value, key*-1))

        # resets beam after pruning
        beam = result

    return result
              

            

        

    

        
    
                
                
        
    

 
            

        
        
        
        
        
        
        


    
        


    

    
        

    
            
    
    
                
    






               

            
