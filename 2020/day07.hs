import Control.Arrow
import Data.Map.Strict (Map)
import qualified Data.Map.Strict as Map
import Text.Regex

solve1 :: Map String [(String, Int)] -> Int
solve1 inp = subtract 1 $ length $ filter (find "shiny gold") $ Map.keys inp
  where
    find tgt src = src == tgt || any (find tgt . fst) (inp Map.! src)

solve2 :: Map String [(String, Int)] -> Int
solve2 = count "shiny gold"
  where
    count src inp = sum $ map (\(t, n) -> n + n * count t inp) (inp Map.! src)

parseInput :: String -> Map String [(String, Int)]
parseInput = Map.fromList . map readLine . lines
  where
    readLine str =
      case matchRegex (mkRegex "^([a-z]+ [a-z]+) bags contain (.*)") str of
        Just [source, parts] -> (source, readParts parts)
        _ -> error $ "Invalid line: " <> show str
    readParts str =
      case matchRegexAll (mkRegex "^([0-9]+) ([a-z]+ [a-z]+) bags?(, |.)") str of
        Just (_, _, rest, [n, part, _]) -> (part, read n) : readParts rest
        _ -> []

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
