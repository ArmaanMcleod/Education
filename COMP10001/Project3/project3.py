from collections import defaultdict

def bid(hand, player_no, phase_no, deck_top, reshuffled=False,
        player_data=None, suppress_player_data=True):
    
    """
    Takes in seven arguements. hand, a tuple of cards in the form of a
    string. player_no, an integer between 0 and 3 indicating the player
    order for the current phase. phase_no, an integer between 1 and 19,
    showing the phase number of the current hand. deck_top, the trump
    card. An optional arguement, reshuffled, defaulting to False, which
    indicates whether the deck was reshuffled. Another optional arguement,
    player_data defaulting to None, conveys a user-defined structure
    of the current game state. Finally, an optional arguement, suppress_
    player_data, defaulting to True, showing if only the bid should be
    returned or with player_data included.

    Returns an integer between 1 and 10 inclusive, indicating the number
    of tricks you want to win.

    bid(tuple<str, str, str, str>, int, int, str, bool, None, bool) -> int
    """

    bid_count = 0

    if phase_no in range(2, 10) or phase_no in range(11, 19):

        # forced bids
        if phase_no % 4 == 0:
            
            if (phase_no == 8 or phase_no == 12):
                bid_count = 2
                
            elif (phase_no == 4 or phase_no == 16):
                bid_count = 1

        # normal rounds
        else:
            bid_count = strategy(hand, deck_top)

    elif phase_no == 10:
        bid_count = 0

    # phases 1 and 19
    else:
        if strategy(hand, deck_top) > 0:
            bid_count = 0
        else:
            bid_count = 1
                
    return bid_count

def strategy(hand, deck_top):

    """
    Takes in hand, and tuple of strings, and a trump card, also in the form
    of a string. Returns strategy bid for normal rounds in game

    strategy(tuple<str>), str) -> int
    """

    high_cards = ["J", "Q", "K", "A"]
    
    value = 0
    suit = 1
    
    bid_count = 0
    for card in hand:

        # checking for trump matches and high valued cards
        if card[suit] == deck_top[suit] and card[value] > deck_top[value]:
            bid_count += 1
        elif card[suit] == deck_top[suit]:
            bid_count += 1
        elif card[value] in high_cards and card[suit] != deck_top[suit]:
            bid_count += 1
            
    return bid_count

def is_valid_play(play, curr_trick, hand):

    """
    Takes in three arguements. play, a card in the form of a string,
    representing a potential play. curr_trick, a tuple of cards, in the
    form of strings, showing the cards that have been played in the
    current round. hand, a tuple of cards that are currently in your
    hand. Returns a boolean, True is a play is valid, False if it is
    invalid.

    is_valid_play(str, tuple<str>, tuple<str>) -> boolean
    """
    
    leading = 0
    suit = 1

    # checking for validity of plays
    if play not in hand:
        return False
    
    if len(curr_trick) == 0 or play[suit] == curr_trick[leading][suit]:
        return True
   
    else:
        leading_suit = curr_trick[leading][suit]

        # adding plays to current gamestate                                 
        current_list = []
        for card in hand:
            current_list.append(card[suit])
 
        if leading_suit not in current_list:
            return True
        return False

def rank_order():
    
    """
    Takes in None. Returns list of card ranks within deck.

    rank_order(None) -> list(str, str, str, str, str, str, str, str, str,

    str, str, str, str, str)
    """
    
    numbers = [str(i) for i in range(2, 10)] + ["0"]
    royals = ["J", "Q", "K", "A"]
    rank_orders = numbers + royals
    
    return rank_orders

def score_phase(bids, tricks, deck_top, player_data=None, 
                suppress_player_data=True):

    """
    Takes in five arguements. bids, a tuple containing the bids in order of
    player_no. tricks, a 4-tuple, each representing a single trick in the
    order of play. deck_top, which is the trump suit. An optional arguement,
    player_data, defaulting to None, which is a user-defined data structure
    of the current game state. Returns a 4-tuple, representing the score for
    each player.

    score_phase(tuple<int, int, int, int>, tuple<<str, str, str, str>>, str,
    
    None, bool) -> tuple<int,int, int, int>
    """

    # 2d array of all the possible winner orders
    winner_order = [[0, 1, 2, 3], [1, 2, 3, 0], [2, 3, 0, 1], [3, 0, 1, 2]]

    leading = 0
    suit = 1

    player_dict = defaultdict(str)
    score_dict = defaultdict(int)
    
    result_tup = ()

    # position count of winner order
    pos = 0

    for play in tricks:

        # Organise ranks in terms of index
        d = defaultdict(int)
        for index, card in enumerate(rank_order()):
            d[card] = index

        # sorts plays from dictionary ranks
        sorted_candidates = sorted(play, 
                                   key=lambda card: (d[card[0]], card[1]))

        # looks for trumps
        trump_matches = []
        for cards in sorted_candidates:
            if cards[1] == deck_top[1]:
                trump_matches.append(cards)
 
        if len(trump_matches) == 0:
            trump = sorted_candidates[leading][suit]
            for cards in sorted_candidates:
                if cards[1] == trump:
                    trump_matches.append(cards)

        # cycles through winner order depending on phase                
        count = 0
        while count < len(winner_order[pos]):
            player_dict[winner_order[pos][count]] = play[count]
            count += 1

        # if a winner is found, add to score
        for player, trick in player_dict.items():
            if trick == trump_matches[-1]:
                score_dict[player] += 1
                pos = player
                
        for player in player_dict:
            score_dict[player] += 0

        # gathes scores of each player
        score_list = []
        for i in score_dict.values():
            score_list.append(i)

        # final calculations of player scores
        for i in range(len(score_list)):
            if bids[i] == score_list[i]:
                result_tup += (score_list[i] + 10,)
            else:
                result_tup += (score_list[i],)

    result_tup = result_tup[-4:]
    return result_tup


def play(curr_trick, hand, prev_tricks, player_no, deck_top, phase_bids,
         player_data=None, suppress_player_data=True,
         is_valid=is_valid_play, score=score_phase):

    """
    Takes in ten arguements. curr_trick, a tuple containing cards in the
    incomplete trick. hand, a tuple of cards in the form of strings, showing
    the cards remaining in your hand for the current phase. prev_tricks, a
    4-tuple which depict the completed tricks of the current phase. player_no,
    an integer between 0 and 3 inclusive, indicating the player order of the
    current phase. deck_top, the trump suit of the current_phase. phase_bids,
    a 4-tuple containing the bids of the players for the current phase, in
    order of player_no. An optional arguement, player_data, defaulting to
    None. Another optional arguement, suppress_player_data, defaulting to
    True. Another optional arguement, id_valid, defaulting to the function
    is_valid_play. Finally, another optional arguement, score, defaulting to
    the function score_phase.

    Returns a single card, represented as a strint, indicating your next play.

    play(tuple<str>, tuple<str>, tuple<str, str, str, str>, int, str,
    tuple<int, int, int, int>, None, bool, function, functon)
    """

    value = 0
    suit = 1

    # initial check, if you are the first player for the current phase
    if len(curr_trick) == 0 and len(hand) >= 1:

        # play options contained in lists
        trump_matches = []
        secondary = []
        for card in hand:
            if card[suit] == deck_top[suit]:
                trump_matches.append(card)
            else:
                secondary.append(card)

        # checking for trumps, returning highest card found        
        if len(trump_matches) == 0:
            return max(secondary, key=lambda c: rank_order().index(c[value]))
        else:
            return max(trump_matches, 
                      key=lambda c: rank_order().index(c[value]))        

    # current tricks have been played
    else:
        # possibilities contained in lists
        suit_matches = []
        secondary = []
        trump_matches = []
        last_choice = []
        
        for card in hand:
            if card[suit] == curr_trick[0][suit]:
                suit_matches.append(card)
            else:
                secondary.append(card)

        # finding trumps
        if len(suit_matches) == 0:
            for card in secondary:
                if card[suit] == deck_top[suit]:
                    trump_matches.append(card)
                else:
                    last_choice.append(card)

            # returns best, highest card
            if len(trump_matches) > 0:
                return max(trump_matches, 
                           key=lambda c: rank_order().index(c[value]))
            else:
                return max(last_choice,
                           key=lambda c: rank_order().index(c[value]))
        # follows suit
        else:
            return max(suit_matches,
                       key=lambda c: rank_order().index(c[value]))

    

        
            
            
            
            
            
            
                
                
                
        
                    

    

                
                
        

    

    

    

    

    
            
            
    
            

    
     

   
        

    


        


        

        
        
     
        
            

        
                
                
                

        
        



        
            

        












