# Palindrome-Finder

Generates palindromes from a dataset of a collection of words.

Functions
-----
There are two top-level functions in this repo that generate palindromes:

* `std::vector<std::string> findAllPalindromes(const std::vector<std::string>& seedWords, int numberOfWords)`

* `std::vector<std::string> findTypedPalindromes(const std::vector<WordType>& types, const EnumMap<WordType, std::vector<std::string>>& words)`

The first accepts a list of words, and a desired palindrome length. It will then find all the palindromes that can be made at that length with those words.

The second allows you to specify an ordered vector of types of words, and a map to a list of words for each type. This allows the specification of something like: adjective + noun + verb + adverb.

Limitations
-----
All matching palindromes are found, which means that 10s or 100s of thousands of palindromes might be found for any word data set of a reasonable size. Most of these palindromes are nonsense ("a a a a a", "tops spot", "racecar racecar racecar"). The ability to choose word types was added in the hope that more meaningful palindrome phrases could be found. Unfortunately, this did not help too much and there is still a huge amount of nonsense. The results could be improved through the choice of better word sets, but categorized word sets are hard to find.

Data Source
-----
The repo contains word data sets taken from the WordNet project. This is one of the few sources that has words categorized by type (noun, adjective, etc.). The words were extracted from the database into a more usable format.

Palindrome examples
-----
Here are some palindromes that were found by the algorithm:
```
damp milt limp mad
yankee see, seek? nay!
wont soho host, now?
wont sulk. lust, now!
tuck wahoo hawk cut
putrid xxx. dirt up!
popeyed racecard eye pop
you bum. u buoy.
```
