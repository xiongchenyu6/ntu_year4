module Module where

precision :: Double
precision = 0.000000000000000000000000001

dichotomy :: Double ->[Double]
dichotomy 0 = [0]
dichotomy x
           | x > 1     = loop x 1 []
           | x > 0     = loop ((x + 1) / 2) 0 []
           | x >= (-1) = loop 0 ((x-1) / 2) []
           | otherwise = loop (-1) x []
           where
             loop max min guessList
                 | guessIsGoodEnough x guess = guessList
                 | otherwise = case guessTooSmallP of
                                 True  -> increaseGuess
                                 False -> decreaseGuess
              where
              guess          = (max + min) / 2
              guessTooSmallP = x - guess ** 3 > 0
              increaseGuess  = loop max guess newGuessList
              decreaseGuess  = loop guess min newGuessList
              newGuessList   = guessList ++ [guess]

newton'sMethod :: Double -> [Double]
newton'sMethod 0    = [0]
newton'sMethod 1    = [1]
newton'sMethod (-1) = [-1]
newton'sMethod x    = loop 1 []
    where
      loop guess guessList
          | guessIsGoodEnough x guess = guessList
          | otherwise                 = loop improvedGuess newGuessList
          where
            fx            = guess ** 3 -x
            f'x           = 2 * guess ** 2
            improvedGuess = guess - fx / f'x
            newGuessList  = guessList ++ [guess]


guessIsGoodEnough :: Double -> Double -> Bool
guessIsGoodEnough x guess = abs (guess ** 3 - x) < abs( precision * x)

main::IO ()
main =
  getLine >>= \method -> putStrLn "Please input number" >>
  getLine >>= \input -> mapM_ print ((length . newton'sMethod $ ( read $ input :: Double)) : (length .dichotomy $ ( read $ input :: Double)) : [])
