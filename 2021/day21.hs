import Control.Arrow
import qualified Data.HashMap.Strict as Map
import Data.List.Split
import Data.Maybe

type State = (Bool, (Int, Int), (Int, Int))

move :: Int -> State -> State
move steps (curr, (pos1, score1), p2) =
  let next1 = (pos1 + steps - 1) `mod` 10 + 1
   in (not curr, p2, (next1, score1 + next1))

solve1 :: (Int, Int) -> Int
solve1 = head . mapMaybe winner . zip [0 ..] . iterate step . initial
  where
    initial (init1, init2) = (dieRolls, (False, (init1, 0), (init2, 0)))
    dieRolls = [1 .. 100] ++ dieRolls

    step (die, st) =
      let (steps, die') = splitAt 3 die
       in (die', move (sum steps) st)

    winner (turn, (_, (_, (_, score1), (_, score2)))) =
      if score2 >= 1000 then Just (score1 * turn * 3) else Nothing

solve2 :: (Int, Int) -> Int
solve2 = maxWinner . concat . takeWhile (not . null) . iterate step . initial
  where
    initial (init1, init2) = [((False, (init1, 0), (init2, 0)), 1)]

    step = Map.toList . Map.fromListWith (+) . concatMap expand . filter (isNothing . winner)
    expand (st, n) = [(move (d1 + d2 + d3) st, n) | d1 <- [1 .. 3], d2 <- [1 .. 3], d3 <- [1 .. 3]]

    winner ((turn, _, (_, score2)), cnt) =
      if score2 >= 21 then Just (not turn, cnt) else Nothing

    maxWinner = maximum . Map.elems . Map.fromListWith (+) . mapMaybe winner

parseInput :: String -> (Int, Int)
parseInput = (head &&& last) . map (read . last . splitOn ": ") . lines

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
