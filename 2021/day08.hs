import Control.Arrow
import Data.Char
import Data.List
import Data.List.Split
import Data.Maybe

digit :: [Char] -> Maybe Int
digit "abcefg" = Just 0
digit "cf" = Just 1
digit "acdeg" = Just 2
digit "acdfg" = Just 3
digit "bcdf" = Just 4
digit "abdfg" = Just 5
digit "abdefg" = Just 6
digit "acf" = Just 7
digit "abcdefg" = Just 8
digit "abcdfg" = Just 9
digit _ = Nothing

segMapping :: [[Char]] -> Char -> Char
segMapping ins = head $ filter isValid $ toFunc <$> permutations ['a' .. 'g']
  where
    isValid f = all (isJust . digit . sort . map f) ins
    toFunc perm ch = perm !! (ord ch - ord 'a')

solve1 :: [([[Char]], [[Char]])] -> Int
solve1 = length . filter (`elem` [2, 3, 4, 7]) . map length . concatMap snd

solve2 :: [([[Char]], [[Char]])] -> Int
solve2 = sum . map match
  where
    digitMapping ins = fromJust . digit . sort . map (segMapping ins)
    match (ins, outs) = read $ concatMap (show . digitMapping ins) outs

parseInput :: String -> [([[Char]], [[Char]])]
parseInput = map ((head &&& last) . map words . splitOn "|") . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
