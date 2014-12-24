# Fun-with-templates [![Build Status](https://travis-ci.org/Globicodeur/Fun-with-templates.svg?branch=master)](https://travis-ci.org/Globicodeur/Fun-with-templates)

experimenting with the c++11/14 standard

## Status
### Functional stuff
#### Lists
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
- [ ] scanl :: (b -> a -> b) -> b -> [a] -> [b]
- [ ] scanl1 :: (a -> a -> a) -> [a] -> [a]
- [ ] scanr :: (a -> b -> b) -> b -> [a] -> [b]
- [ ] scanr1 :: (a -> a -> a) -> [a] -> [a]

###### Accumulating
- [ ] mapAccumL :: (acc -> x -> (acc, y)) -> acc -> [x] -> (acc, [y])
- [ ] mapAccumR :: (acc -> x -> (acc, y)) -> acc -> [x] -> (acc, [y])

##### Unfolding
- [ ] unfoldr :: (b -> Maybe (a, b)) -> b -> [a]

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
- [ ] stripPrefix :: Eq a => [a] -> [a] -> Maybe [a]
- [ ] group :: Eq a => [a] -> [[a]]
- [ ] inits :: [a] -> [[a]]
- [ ] tails :: [a] -> [[a]]

###### Predicates
- [ ] isPrefixOf :: Eq a => [a] -> [a] -> Bool
- [ ] isSuffixOf :: Eq a => [a] -> [a] -> Bool
- [ ] isInfixOf :: Eq a => [a] -> [a] -> Bool

##### Searching
- [x] elem :: Eq a => a -> [a] -> Bool
- [x] notElem :: Eq a => a -> [a] -> Bool
- [x] lookup :: Eq a => a -> [(a, b)] -> Maybe b
- [x] find :: (a -> Bool) -> [a] -> Maybe a
- [x] filter :: (a -> Bool) -> [a] -> [a]
- [x] partition :: (a -> Bool) -> [a] -> ([a], [a])

##### Indexing
- [ ] !! :: [a] -> Int -> a
- [ ] elemIndex :: Eq a => a -> [a] -> Maybe Int
- [ ] elemIndices :: Eq a => a -> [a] -> [Int]
- [ ] findIndex :: (a -> Bool) -> [a] -> Maybe Int
- [ ] findIndices :: (a -> Bool) -> [a] -> [Int]

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
