import Control.Arrow
import Data.Bits
import Data.IntMap (IntMap)
import qualified Data.IntMap.Strict as Map
import Data.Vector (Vector)
import qualified Data.Vector as Vec
import Text.Regex

type Instr = (String, Int, Int, Int)

step :: Instr -> IntMap Int -> IntMap Int
step (op, a, b, c) reg = Map.insert c (getResult op) reg
  where
    getr = (reg Map.!)
    getResult "addr" = getr a + getr b
    getResult "addi" = getr a + b
    getResult "mulr" = getr a * getr b
    getResult "muli" = getr a * b
    getResult "banr" = getr a .&. getr b
    getResult "bani" = getr a .&. b
    getResult "borr" = getr a .|. getr b
    getResult "bori" = getr a .|. b
    getResult "setr" = getr a
    getResult "seti" = a
    getResult "gtir" = fromEnum $ a > getr b
    getResult "gtri" = fromEnum $ getr a > b
    getResult "gtrr" = fromEnum $ getr a > getr b
    getResult "eqir" = fromEnum $ a == getr b
    getResult "eqri" = fromEnum $ getr a == b
    getResult "eqrr" = fromEnum $ getr a == getr b
    getResult op' = error $ "Illegal operation: " <> op'

runProg :: (Int, Vector Instr) -> IntMap Int -> Int
runProg (ipIdx, prog) reg = case prog Vec.!? (reg Map.! ipIdx) of
  Just instr -> runProg (ipIdx, prog) $ Map.adjust (+ 1) ipIdx $ step instr reg
  Nothing -> reg Map.! 0

solve1 :: (Int, Vector Instr) -> Int
solve1 = flip runProg $ Map.fromList $ zip [0 ..] $ replicate 6 0

solve2 :: (Int, Vector Instr) -> Int
solve2 _ = sum $ filter (\x5 -> x1 `mod` x5 == 0) [1 .. x1]
  where
    x1 = 10551292

parseInput :: String -> (Int, Vector Instr)
parseInput = (parseIp . head &&& Vec.fromList . map parseInstr . tail) . lines
  where
    parseIp str =
      case matchRegex (mkRegex "#ip ([0-5])") str of
        Just [idx] -> read idx
        _ -> error $ "Illegal #ip declaration: " <> str
    parseInstr str =
      case matchRegex (mkRegex "([a-z]+) ([0-9]+) ([0-9]+) ([0-9]+)") str of
        Just [op, argA, argB, argC] -> (op, read argA, read argB, read argC)
        _ -> error $ "Illegal #ip declaration: " <> str

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
