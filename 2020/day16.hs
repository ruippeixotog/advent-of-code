{-# LANGUAGE OverloadedStrings #-}

import Control.Arrow
import Data.Ix
import Data.List
import qualified Data.Text as T
import Text.Regex

type Rule = ((Int, Int), (Int, Int))

type Input = ([(String, Rule)], [[Int]])

isValid :: Int -> Rule -> Bool
isValid v (r1, r2) = inRange r1 v || inRange r2 v

solve1 :: Input -> Int
solve1 (fields, ts) = sum $ concatMap (filter isInvalidVal) ts
  where
    isInvalidVal v = not $ any (isValid v . snd) fields

solve2 :: Input -> Int
solve2 (fields, ts) =
  product $ map snd $ filter (isPrefixOf "departure" . fst) $
    resolve [] $ map (id &&& validNames) $ transpose $ filter isValidTix ts
  where
    isValidTix = all $ \v -> any (isValid v . snd) fields
    validNames col = map fst $ filter (\(_, rule) -> all (`isValid` rule) col) fields

    resolve _ [] = []
    resolve found ((col, [name]) : rest) = (name, head col) : resolve (name : found) rest
    resolve found ((col, names) : rest) =
      let newNames = [name | name <- names, name `notElem` found]
       in resolve found $ rest ++ [(col, newNames)]

parseInput :: String -> Input
parseInput str =
  case matchRegex inputRegex str of
    Just [fields, mt, nts] -> (map readField $ lines fields, readTicket mt : map readTicket (lines nts))
    _ -> error $ "Invalid input: " <> str
  where
    inputRegex = mkRegexWithOpts "(.+)\n\nyour ticket:\n(.+)\n\nnearby tickets:\n(.+)" False True
    fieldRegex = mkRegex "([^:]+): ([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+)"

    readTicket = map (read . T.unpack) . T.splitOn "," . T.pack
    readField fieldStr =
      case matchRegex fieldRegex fieldStr of
        Just [name, low1, hi1, low2, hi2] -> (name, ((read low1, read hi1), (read low2, read hi2)))
        _ -> error $ "Invalid field: " <> fieldStr

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
