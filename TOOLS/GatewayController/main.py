import gateway


if __name__ == '__main__':

    myGateway = gateway.Gateway('COM9')

    # myGateway.setRFSettings(rfSettings)

    rfSettings = gateway.getDefaultLoRaConfig()

    myGateway.setNewRFsettings(rfSettings, broadcast=False)

    while True:
        print(myGateway.readLine())

