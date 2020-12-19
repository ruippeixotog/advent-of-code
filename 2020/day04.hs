import Control.Arrow
import Data.List.Split
import Data.Map.Strict (Map)
import qualified Data.Map.Strict as Map
import Data.Maybe
import Text.Regex

rules1 :: [(String, Regex)]
rules1 = map (second $ \_ -> mkRegex ".*") rules2

rules2 :: [(String, Regex)]
rules2 =
  [ ("byr", mkRegex "^(19[2-9][0-9]|200[0-2])$"),
    ("iyr", mkRegex "^(201[0-9]|2020)$"),
    ("eyr", mkRegex "^(202[0-9]|2030)$"),
    ("hgt", mkRegex "^((1[5-8][0-9]|19[0-3])cm|(59|6[0-9]|7[0-6])in)$"),
    ("hcl", mkRegex "^#[0-9a-f]{6}$"),
    ("ecl", mkRegex "^(amb|blu|brn|gry|grn|hzl|oth)$"),
    ("pid", mkRegex "^[0-9]{9}$")
  ]

validate :: [(String, Regex)] -> Map String String -> Bool
validate rules pass =
  all (\(key, reg) -> isJust $ matchRegex reg =<< pass Map.!? key) rules

solve1 :: [Map String String] -> Int
solve1 = length . filter (validate rules1)

solve2 :: [Map String String] -> Int
solve2 = length . filter (validate rules2)

parseInput :: String -> [Map String String]
parseInput = map parsePass . splitOn "\n\n"
  where
    parsePass = Map.fromList . map (second tail . span (/= ':')) . words

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
