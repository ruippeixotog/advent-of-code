import Control.Arrow
import Text.Regex

solve1 :: [(Int, Int, Char, String)] -> Int
solve1 = length . filter isValid
  where
    between low hi x = x >= low && x <= hi
    isValid (low, hi, ch, pass) = between low hi $ length $ filter (ch ==) pass

solve2 :: [(Int, Int, Char, String)] -> Int
solve2 = length . filter isValid
  where
    isValid (low, hi, ch, pass) =
      (pass !! (low - 1) == ch) /= (pass !! (hi - 1) == ch)

parseInput :: String -> [(Int, Int, Char, String)]
parseInput = map readLine . lines
  where
    readLine str =
      case matchRegex (mkRegex "([0-9]+)-([0-9]+) (.): ([a-z]+)") str of
        Just [low, hi, ch, pass] -> (read low, read hi, head ch, pass)
        _ -> error $ "Invalid line: " <> show str

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
