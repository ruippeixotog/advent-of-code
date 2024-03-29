import Control.Arrow
import Data.List
import qualified Data.Map as Map
import Text.Regex

data Cube = Cube {cIdx :: Int, cIsOn :: Bool, cStart :: [Int], cEnd :: [Int]} deriving (Eq)

solve1 :: [Cube] -> Int
solve1 = solve2 . filter valid
  where
    valid (Cube _ _ st end) = all (> (-50)) (st ++ end) && all (< 50) (st ++ end)

solve2 :: [Cube] -> Int
solve2 [] = 0
solve2 xs@((Cube _ _ [] []) : _) = fromEnum $ cIsOn $ last $ sortOn cIdx xs
solve2 xs = fst $ Map.foldlWithKey step initial $ Map.fromListWith (++) $ concatMap toEvents xs
  where
    initial = (0, (minBound, []))

    toEvents (Cube idx b (x0 : rest0) (x1 : rest1)) =
      let newCube = Cube idx b rest0 rest1
       in [(x0, [Left newCube]), (x1 + 1, [Right newCube])]
    toEvents _ = error "Unexpected zero-dimension cube"

    step (cnt, (prev, active)) curr events =
      let newActive = foldr (either (:) delete) active events
       in (cnt + (curr - prev) * solve2 active, (curr, newActive))

parseInput :: String -> [Cube]
parseInput = zipWith parseLine [0 ..] . lines
  where
    parseLine idx str =
      case matchRegex (mkRegex "(on|off) x=([-0-9]+)..([-0-9]+),y=([-0-9]+)..([-0-9]+),z=([-0-9]+)..([-0-9]+)") str of
        Just [cmd, x0, x1, y0, y1, z0, z1] ->
          Cube idx (cmd == "on") (read <$> [x0, y0, z0]) (read <$> [x1, y1, z1])
        _ -> error $ "Invalid line: " <> show str

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
