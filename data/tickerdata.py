import sys

import yfinance as yf

if __name__ == "__main__":
    
    if len(sys.argv) > 1:
        
        ticker_code: str = sys.argv[1]
        ticker = yf.Ticker(ticker_code)
        
        df = ticker.history(period="max", interval="1d")
        df.to_csv('history.csv')
        
        info = ticker.get_info()
        tickerInfo = open("ticker.txt", 'w')
    
        tickerInfo.write(f"name:{info.get('shortName')}\n")
        tickerInfo.write(f"sector:{info.get('sector')}\n")
        
        tickerInfo.close()
        