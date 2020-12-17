import Control.Arrow
import Data.Bits
import qualified Data.Map as Map
import Text.Regex

data Instr = Mask String | Mem Int Int

solve1 :: [Instr] -> Int
solve1 = sum . Map.elems . snd . foldl runInstr ([], Map.empty)
  where
    runInstr (_, mem) (Mask mask) = (zip [0 ..] $ reverse mask, mem)
    runInstr (mask, mem) (Mem addr val) = (mask, Map.insert addr (foldl apply val mask) mem)

    apply val (n, '0') = clearBit val n
    apply val (n, '1') = setBit val n
    apply val _ = val

solve2 :: [Instr] -> Int
solve2 = sum . Map.elems . snd . foldl runInstr ([], Map.empty)
  where
    runInstr (_, mem) (Mask mask) = (zip [0 ..] $ reverse mask, mem)
    runInstr (mask, mem) (Mem addr val) = (mask, insertAll (foldl apply [addr] mask) val mem)
    insertAll keys val = flip (foldr $ flip Map.insert val) keys

    apply addrs (_, '0') = addrs
    apply addrs (n, '1') = map (`setBit` n) addrs
    apply addrs (n, _) = [op addr n | op <- [setBit, clearBit], addr <- addrs]

parseInput :: String -> [Instr]
parseInput = map parseInstr . lines
  where
    parseInstr str =
      case flip matchRegex str . mkRegex <$> ["mask = (.+)", "mem\\[([0-9]+)\\] = (.+)"] of
        [Just [mask], _] -> Mask mask
        [_, Just [addr, val]] -> Mem (read addr) (read val)
        _ -> error $ "Invalid instruction: " <> str

main :: IO ()
main = interact $ show . (solve1 &&& solve2) . parseInput
