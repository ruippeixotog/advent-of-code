import Control.Arrow
import Data.Either
import Data.List
import Data.Maybe

score :: [Char] -> [Char] -> Either Int Int
score st [] = Right $ foldl (\val ch -> 5 * val + ch) 0 $ cost <$> st
  where
    cost ch = 1 + fromJust (elemIndex ch ['(', '[', '{', '<'])
score ('(' : st) (')' : rest) = score st rest
score ('[' : st) (']' : rest) = score st rest
score ('{' : st) ('}' : rest) = score st rest
score ('<' : st) ('>' : rest) = score st rest
score _ (')' : _) = Left 3
score _ (']' : _) = Left 57
score _ ('}' : _) = Left 1197
score _ ('>' : _) = Left 25137
score st (ch : rest) = score (ch : st) rest

solve1 :: [[Char]] -> Int
solve1 = sum . lefts . map (score [])

solve2 :: [[Char]] -> Int
solve2 = mid . sort . rights . map (score [])
  where
    mid xs = xs !! (length xs `div` 2)

parseInput :: String -> [[Char]]
parseInput = lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
