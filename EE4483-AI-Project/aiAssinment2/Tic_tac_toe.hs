import Data.Array
import Data.List (intercalate, intersperse,elemIndex)
import Data.Tree

data Cell = B | X | O
  deriving (Enum, Read, Eq, Ord)

instance Show Cell where
  show B = "."
  show X    = "X"
  show O    = "O"

opposite :: Cell -> Cell
opposite B = B
opposite X = O
opposite O = X

type Position = (Int, Int)
type State = Array Position Cell

newGame :: State
newGame = listArray boardInds $ repeat B
        where boardInds = ((0,0), (2,2))

update :: State -> (Position, Cell) -> State
update st pc = st // [pc]

getTurn :: State -> Cell
getTurn st
  | pieceDiff == 0    = X
  | pieceDiff == 1    = O
  | otherwise = error "encountered invalid board state"
  where pieceDiff = (count X st) - (count O st)
        count cell state = length . filter (==cell) $ elems state

lookupCell :: State -> Position -> Cell
lookupCell = (!)

getRow, getCol :: State -> Int -> [Cell]
getRow s i = [ lookupCell s (i,j) | j <- [0,1,2] ]
getCol s i = [ lookupCell s (j,i) | j <- [0,1,2] ]

getDiag, getAntiDiag :: State -> [Cell]
getDiag s = [ lookupCell s (i,j) | (i,j) <- [(0,0), (1,1), (2,2)] ]
getAntiDiag s = [ lookupCell s (i,j) | (i,j) <- [(2,0), (1,1), (0,2)] ]

win :: Cell -> State -> Bool
win piece state = checkRows || checkCols || checkDiag || checkAntiDiag
  where checkWin piece list = all (==piece) list
        checkRows = any (==True) [checkWin piece $ getRow state i | i <- [0,1,2]]
        checkCols = any (==True) [checkWin piece $ getCol state i | i <- [0,1,2]]
        checkDiag = checkWin piece $ getDiag state
        checkAntiDiag = checkWin piece $ getAntiDiag state

draw :: State -> Bool
draw st = (length . filter (/=B) $ elems st) == 9

moves :: State -> [State]
moves st
  | win X st || win O st = []
  | otherwise = map (\p -> update st (p, getTurn st)) (freePositions st)
  where freePositions st = filter (\p -> st ! p == B) $ indices newGame


pprint :: State -> IO ()
pprint st = putStrLn $ pretty
         where chars = concat $ map show $ elems st
               rows = [0..2] >>= \i -> return $ take 3 (drop (3*i) chars)
               pretty = intercalate "\n" rows


generate :: State -> Tree State
generate = unfoldTree (\s -> (s, moves s))

prune :: Int -> Tree a -> Tree a
prune 0 t = Node (rootLabel t) []
prune n t = Node (rootLabel t) (map (prune (n-1)) (subForest t))

staticVal :: State -> Int
staticVal = marks

marks :: State -> Int
marks state = checkRows + checkCols + checkDiag + checkAntiDiag
  where getMarks list = case (count X list) - (count O list) of
                          3 -> 1000
                          2 -> 5
                          -2 -> -5
                          -3 -> -1000
                          _ -> 0
        checkRows = sum [getMarks $ getRow state i | i <- [0,1,2]]
        checkCols = sum [getMarks $ getCol state i | i <- [0,1,2]]
        checkDiag = getMarks $ getDiag state
        checkAntiDiag = getMarks $ getAntiDiag state
        count cell list = length . filter (==cell) $ list

mapmin :: Ord a => [[a]] -> [a]
mapmin [] = []
mapmin (xs:rest) = (omit n rest)
  where n = minimum xs
        omit n [] = [n]
        omit n (xs:rest) | minleq n xs = omit n rest
                         | otherwise   = omit k rest
                             where k = minimum xs
        minleq _ [] = False
        minleq n (y:ys) | y <= n = True
                        | otherwise = minleq n ys

mapmax :: Ord t => [[t]] -> [t]
mapmax [] = []
mapmax (xs:rest) = (omit n rest)
  where n = maximum xs
        omit n [] = [n]
        omit n (xs:rest) | maxleq n xs = omit n rest
                          | otherwise   = omit k rest
                              where k = maximum xs
        maxleq _ [] = False
        maxleq n (y:ys) | y >= n = True
                        | otherwise = maxleq n ys

abMaxList :: (Ord a) => Tree a -> [a]
abMaxList (Node x []) = [x]
abMaxList (Node x subs) = mapmin . map abMinList $ subs

abMinList :: (Ord a) => Tree a -> [a]
abMinList (Node x []) = [x]
abMinList (Node x subs) = mapmax . map abMaxList $ subs

minIndex :: Ord a => [a] -> Int
minIndex xs = head $ filter ((== minimum xs) . (xs !!)) [0..]

maxIndex :: Ord a => [a] -> Int
maxIndex xs = head $ filter ((== maximum xs) . (xs !!)) [0..]

abmax :: State -> Int
abmax = maximum .
        abMaxList .
        fmap staticVal .
        prune 4 .
        generate

abmin :: State -> Int
abmin = minimum .
           abMinList .
           fmap staticVal .
           prune 4 .
          generate

playX :: State -> State
playX s = moves s !! (maxIndex . fmap abmin $ moves s)

playO :: State -> State
playO s = moves s !! (minIndex . fmap abmax $ moves s)

playAi :: State -> State
playAi s = case getTurn s of
           X -> playX s
           _ -> playO s

playHuman :: State -> Position -> State
playHuman s p = update s (p,(getTurn s))

main :: IO ()
main = putStrLn "Welcome to the Heuristic Tic Tac Toe" >>
       putStrLn "Below show the board, the up left is the root" >>
       putStrLn "Please decide you want to play first or second (X or O)" >>
       putStrLn "X stand for play first" >>
       fmap (read::String -> Cell) getLine >>= loop newGame

loop:: State -> Cell -> IO()
loop s c
    | c == X =
        if win O s then
            pprint s >>
            putStrLn "Owin"
          else
            if win X s then
                  pprint s >>
                  putStrLn "Xwin"
              else
                if draw s then
                    pprint s >>
                    putStrLn "Draw"
                else
                    pprint s >>
                    putStrLn "Please input as (x,y) such as (0,0) 0<=x<=2, 0<=y<=2" >>
                    fmap (read::String -> Position) getLine >>=
                    \p -> loop  (playHuman s p) (opposite  c)
    | otherwise =
        if win O s then
            pprint s >>
            putStrLn "Owin"
          else
            if win X s then
                  pprint s >>
                  putStrLn "Xwin"
              else
                if draw s then
                    pprint s >>
                    putStrLn "Draw"
                else
                  pprint s >>
                  putStrLn "Now please wait AI to calculate" >>
                  loop (playAi s) (opposite c)
