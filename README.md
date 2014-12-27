# Fun-with-templates [![Build Status](https://travis-ci.org/Globicodeur/Fun-with-templates.svg?branch=master)](https://travis-ci.org/Globicodeur/Fun-with-templates)

experimenting with the c++11/14 standard

## Status

### Functional stuff

In this part of the library, we will abuse [CRTP](http://wikipedia.org/wiki/Curiously_recurring_template_pattern) and parenthesis operator overloading to provide composable *function objects* able to achieve [Parameteric polymorphism](http://wikipedia.org/wiki/Parametric_polymorphism).

#### Lists

This module will provide useful and generic functions to operate on containers.  
I will use [Haskell's Data.List package](http://hackage.haskell.org/package/base-4.7.0.1/docs/Data-List.html) as a specification.  
The functions should be guaranteed to work with any [sequence container](http://en.cppreference.com/w/cpp/container#Sequence_containers) templated with one mandatory type and satisfying (at least) the concept of [input iterator](http://en.cppreference.com/w/cpp/concept/InputIterator)

##### Basic functions
- [x] ++ :: [a] -> [a] -> [a] **named append**
- [x] head :: [a] -> a
- [x] last :: [a] -> a
- [x] tail :: [a] -> [a]
- [x] init :: [a] -> [a]
- [x] null :: [a] -> Bool
- [x] length :: [a] -> Int

##### Transformations
- [x] map :: (a -> b) -> [a] -> [b]
- [x] reverse :: [a] -> [a]
- [x] intersperse :: a -> [a] -> [a]
- [x] intercalate :: [a] -> [[a]] -> [a]
- [ ] transpose :: [[a]] -> [[a]]
- [ ] subsequences :: [a] -> [[a]]
- [ ] permutations :: [a] -> [[a]]

##### Folds
###### Basic
- [x] foldl :: (b -> a -> b) -> b -> [a] -> b
- [x] foldl1 :: (a -> a -> a) -> [a] -> a
- [x] foldr :: (a -> b -> b) -> b -> [a] -> b
- [x] foldr1 :: (a -> a -> a) -> [a] -> a

###### Special
- [x] concat :: [[a]] -> [a]
- [x] concatMap :: (a -> [b]) -> [a] -> [b]
- [x] and :: [Bool] -> Bool
- [x] or :: [Bool] -> Bool
- [x] any :: (a -> Bool) -> [a] -> Bool
- [x] all :: (a -> Bool) -> [a] -> Bool
- [x] sum :: Num a => [a] -> a
- [x] product :: Num a => [a] -> a
- [x] maximum :: Ord a => [a] -> a
- [x] minimum :: Ord a => [a] -> a

##### Building
###### Scans
- [x] scanl :: (b -> a -> b) -> b -> [a] -> [b]
- [x] scanl1 :: (a -> a -> a) -> [a] -> [a]
- [x] scanr :: (a -> b -> b) -> b -> [a] -> [b]
- [x] scanr1 :: (a -> a -> a) -> [a] -> [a]

###### Accumulating
- [x] mapAccumL :: (acc -> x -> (acc, y)) -> acc -> [x] -> (acc, [y])
- [x] mapAccumR :: (acc -> x -> (acc, y)) -> acc -> [x] -> (acc, [y])

###### Unfolding
- [x] unfoldr :: (b -> Maybe (a, b)) -> b -> [a]

##### Sublists
###### Extractions
- [x] take :: Int -> [a] -> [a]
- [x] drop :: Int -> [a] -> [a]
- [x] splitAt :: Int -> [a] -> ([a], [a])
- [x] takeWhile :: (a -> Bool) -> [a] -> [a]
- [x] dropWhile :: (a -> Bool) -> [a] -> [a]
- [x] dropWhileEnd :: (a -> Bool) -> [a] -> [a]
- [x] span :: (a -> Bool) -> [a] -> ([a], [a])
- [x] break :: (a -> Bool) -> [a] -> ([a], [a])
- [x] stripPrefix :: Eq a => [a] -> [a] -> Maybe [a]
- [x] group :: Eq a => [a] -> [[a]]
- [x] inits :: [a] -> [[a]]
- [x] tails :: [a] -> [[a]]

###### Predicates
- [x] isPrefixOf :: Eq a => [a] -> [a] -> Bool
- [x] isSuffixOf :: Eq a => [a] -> [a] -> Bool
- [x] isInfixOf :: Eq a => [a] -> [a] -> Bool

##### Searching
- [x] elem :: Eq a => a -> [a] -> Bool
- [x] notElem :: Eq a => a -> [a] -> Bool
- [x] lookup :: Eq a => a -> [(a, b)] -> Maybe b
- [x] find :: (a -> Bool) -> [a] -> Maybe a
- [x] filter :: (a -> Bool) -> [a] -> [a]
- [x] partition :: (a -> Bool) -> [a] -> ([a], [a])

##### Indexing
- [x] !! :: [a] -> Int -> a
- [x] elemIndex :: Eq a => a -> [a] -> Maybe Int
- [x] elemIndices :: Eq a => a -> [a] -> [Int]
- [x] findIndex :: (a -> Bool) -> [a] -> Maybe Int
- [x] findIndices :: (a -> Bool) -> [a] -> [Int]

##### Zipping
- [x] zip :: [a] -> [b] -> [(a, b)] **made variadic**
- [x] zipWith :: (a -> b -> c) -> [a] -> [b] -> [c] **made variadic**
- [x] unzip :: [(a, b)] -> ([a], [b]) **made variadic**

##### Special lists
###### Strings
- [ ] lines :: String -> [String]
- [ ] words :: String -> [String]
- [ ] unlines :: [String] -> String
- [ ] unwords :: [String] -> String

###### *Set* operations
- [ ] nub :: Eq a => [a] -> [a]
- [ ] delete :: Eq a => a -> [a] -> [a]
- [ ] \\\\ :: Eq a => [a] -> [a] -> [a]
- [ ] union :: Eq a => [a] -> [a] -> [a]
- [ ] intersect :: Eq a => [a] -> [a] -> [a]

###### Ordered lists
- [ ] sort :: Ord a => [a] -> [a]
- [ ] insert :: Ord a => a -> [a] -> [a]

##### Generalized functions
- [ ] nubBy :: (a -> a -> Bool) -> [a] -> [a]
- [ ] deleteBy :: (a -> a -> Bool) -> a -> [a] -> [a]
- [ ] deleteFirstsBy :: (a -> a -> Bool) -> [a] -> [a] -> [a]
- [ ] unionBy :: (a -> a -> Bool) -> [a] -> [a] -> [a]
- [ ] intersectBy :: (a -> a -> Bool) -> [a] -> [a] -> [a]
- [ ] groupBy :: (a -> a -> Bool) -> [a] -> [[a]]
- [ ] sortBy :: (a -> a -> Ordering) -> [a] -> [a]
- [ ] insertBy :: (a -> a -> Ordering) -> a -> [a] -> [a]
- [ ] maximumBy :: (a -> a -> Ordering) -> [a] -> a
- [ ] minimumBy :: (a -> a -> Ordering) -> [a] -> a
