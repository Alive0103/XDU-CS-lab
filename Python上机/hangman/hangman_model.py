# 函数 1：单词是否被猜中
def isWordGuessed(secretWord, lettersGuessed):
    '''
    参数：
       - secretWord: 字符串
       - lettersGuessed：字符列表
    函数返回一个布尔值
       - True：如果 secretWord 被正确猜到 
       (也就是说, 在 secretWord 中的所有字母都在 lettersGuessed中)
       - False：其他情况。
    假设参数中包含的所有字母都是小写。
    '''
    # 






# 函数 2：打印猜测的单词
def getGuessedWord(secretWord, lettersGuessed):
    '''函数基于 lettersGuessed 列表中的字母是否在 secretWord 中， 
    返回一个由字母和下划线组成的字符串。
    参数：
       - secretWord: 字符串
       - lettersGuessed：字符列表
    返回值：
       - 字符串：由字母和下划线组成
    '''
    # 



# 函数 3： 打印可用（还未猜过的）字母
def getAvailableLetters(lettersGuessed):
    '''
    参数：
      - lettersGuessed：字符列表
    返回值：
      - 一个按照字母顺序排序的，由小写英文字母构成的字符串；
      返回的字符串中不包含已经在 lettersGuessed 中的字母。
    假设参数lettersGuessed中包含的所有字母都是小写。

    '''
    # 




# 函数 4：实现 hangman函数
def hangman(secretWord):
    '''带有一个参数secretWord，参数用来表示用户要猜的单词。
    我们将整个Hangman游戏分解为4个函数，以下3个函数已经实现：
    isWordGuessed
    getGuessedWord
    getAvailableLetters,
    每次玩家猜一个字母之后，所猜的字母要从可用字母列表中删除。
    如果所猜的字母不在可用字母列表中，那就需要提醒玩家已经猜过这个字母了，再试一次。'''
    # 





    

# -----------------------------------

# 以下是两个帮助函数
import random

WORDLIST_FILENAME = "./words.txt" 
# 如果单词文件和程序不在同一个目录下，使用绝对路径

def loadWords():
    """
    返回值：单词的列表；每个单词是由小写字母构成的字符串。
    函数运行时间和列表的大小有关。
    """
    print("从文件中加载单词列表...")
    with open(WORDLIST_FILENAME, 'r') as inFile:
        line = inFile.readline()
    wordlist = line.split()
    print("  加载了", len(wordlist), "个单词。")
    return wordlist

def chooseWord(wordlist):
    """
    参数：
      - wordlist：单词列表
    返回值：
      - 从单词列表随机返回一个单词"""
    return random.choice(wordlist)

# -----------------------------------



# 加载函数，返回单词列表
wordlist = loadWords()

# 测试
secretWord = chooseWord(wordlist).lower()
hangman(secretWord)