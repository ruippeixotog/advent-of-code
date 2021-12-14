{-# LANGUAGE TupleSections #-}

import Control.Arrow
import Data.List.Split
import Data.Map (Map)
import qualified Data.Map.Strict as Map

type Pair = (Char, Char)

toPairHist :: String -> Map Pair Int
toPairHist (c1 : c2 : rest) = Map.insertWith (+) (c1, c2) 1 $ toPairHist (c2 : rest)
toPairHist _ = Map.empty

expand :: Map Pair Char -> Map Pair Int -> Map Pair Int
expand rules =
  Map.fromListWith (+) . concatMap (\(p, cnt) -> (,cnt) <$> expandPair p) . Map.toList
  where
    expandPair (c1, c2) = let c = rules Map.! (c1, c2) in [(c1, c), (c, c2)]

score :: String -> Map Pair Int -> Int
score [] = error "Empty string"
score (ch0 : _) = uncurry (-) . (maximum &&& minimum) . Map.elems . toCharHist
  where
    toCharHist = Map.adjust (+ 1) ch0 . Map.mapKeysWith (+) snd

solve1 :: (String, Map Pair Char) -> Int
solve1 (str, rules) = score str $ (!! 10) $ iterate (expand rules) $ toPairHist str

solve2 :: (String, Map Pair Char) -> Int
solve2 (str, rules) = score str $ (!! 40) $ iterate (expand rules) $ toPairHist str

parseInput :: String -> (String, Map Pair Char)
parseInput = (head &&& Map.fromList . map parseRule . lines . last) . splitOn "\n\n"
  where
    parseRule :: String -> (Pair, Char)
    parseRule = ((head &&& last) . head &&& head . last) . splitOn " -> "

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
