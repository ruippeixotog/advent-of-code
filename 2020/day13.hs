{-# LANGUAGE TupleSections #-}

import Control.Arrow
import Data.List.Split
import Data.Maybe
import Text.Read

solve1 :: (Int, [(Int, Int)]) -> Int
solve1 (n, schs) = uncurry (*) $ minimum $ map ((waitTime &&& id) . snd) schs
  where
    waitTime sch = sch - n `mod` sch

solve2 :: (Int, [(Int, Int)]) -> Int
solve2 (_, schs) = sync 0 1 schs
  where
    sync t _ [] = t
    sync t delta schs'@((i, sch) : rest)
      | (t + i) `mod` sch == 0 = sync t (delta * sch) rest
      | otherwise = sync (t + delta) delta schs'

parseInput :: String -> (Int, [(Int, Int)])
parseInput str =
  case lines str of
    [n, schs] -> (read n, readSchs schs)
    _ -> error $ "Illegal input: " <> str
  where
    readSchs = mapMaybe (\(i, sch) -> (i,) <$> readMaybe sch) . zip [0 ..] . splitOn ","

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
