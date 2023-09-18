# Functions to be coded this week (monday 18th september - wednesday 20th september)

readSpells():
  a) takes the name of a text file
  b) prints the spells in a table format with 5 words per line separated by tab spaces
  c) returns a (pointer to a) 2D array containing the spells from the file in one column and 1’s in the other
note: the 2D array acts as a hashmap, with the spell name as the key and the binary (0,1) to show whether the spell has been used before. the spells will have initially have 1 as the corresponding value

tossCoin(): 
  a) takes the player names as parameters
  b) randomly chooses either player 1 or player 2 to start
  c) returns the name of the player who will be starting

checkMove(): 
  a) takes (a pointer to) the 2D array containing the spells, the previously used spell (or the last character of the spell), and the spell cast by the current player as parameters
  b) loops once through the 2D array containing the spells, comparing each spell to the spell cast
      i) if the spell is found, checks if the spell has been used before:
          1) if the spell has been used before, the function returns “the spell has been used before! the current player loses!” 
          2) if the spell has not been used before, checks if the first character of the spell cast is the same the last character of the previously cast spell
              a) if the characters are the same, return “the spell case is valid. next player’s turn!”
              b) if the characters are different, return “the spell cast begins with the wrong character! the current player loses!”
      ii) if the spell is not found, returns “the spell cast is not in the list! the current player loses!”

