def main():
    while True:
        user_input = input("请输入您的问题：")
        print("思考中...")
        num = randint(1,4)
        sleep(num)
        print("服务器繁忙，请稍后再试。")
        
if __name__ == '__main__':
    main()
