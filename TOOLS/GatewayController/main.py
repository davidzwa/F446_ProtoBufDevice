import gateway


if __name__ == '__main__':

    myGateway = gateway.Gateway('COM6')

    while True:
        print(myGateway.readLine())

