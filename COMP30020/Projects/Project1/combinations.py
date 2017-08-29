import itertools

MUSICAL_NOTES = ["A", "B", "C"]
MUSICAL_OCTAVES = [str(i) for i in range(1, 4)]
MAX_PITCHES = 3

def combinations(notes, octaves):
    combinations = []
    for note in notes:
        for octave in octaves:
            combinations.append(note + octave)

    return combinations

def k_combinations(lst, k):
    return [list(item) for item in itertools.combinations(lst, k)]

def feedback(lst, target):
    feedback_list = []

    for chord in lst:
        correct_pitches = 0
        correct_notes = 0
        correct_octaves = 0

        for pitch in chord:
            if pitch in target:
                correct_pitches += 1

        if correct_pitches < MAX_PITCHES:
            temp = chord[:]
            target_temp = target[:]
            for note in temp:
                if note in target_temp:
                    temp.remove(note)
                    target_temp.remove(note)

            for note1 in temp:
                for note2 in target_temp:
                    if note1[0] == note2[0]:
                        correct_notes += 1
                    if note1[1] == note2[1]:
                        correct_octaves += 1

        current_feedback = [correct_pitches, correct_notes, correct_octaves]
        feedback_list.append(current_feedback)

    return feedback_list



possible_combs = k_combinations(combinations(MUSICAL_NOTES, MUSICAL_OCTAVES), 3)
print(possible_combs)

candidate_target = ["A1", "B2", "C3"]

possible_feedback = feedback(possible_combs, candidate_target)

print(possible_feedback)






