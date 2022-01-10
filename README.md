# MathParser
Mathematical Parser that I wrote and later based my Graphic Work parser on it

## Working Principle

* The parser accepts a string with mathematical expression
* The parser divides the string into characters and adds them to different maps that represent the character types (they are sorted using CharTypes class)
* The parser than unites character numbers into ones using indexes
* The parser iterates each bracket, counts result of expreession in it
* The parser returns final results 
