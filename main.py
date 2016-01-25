import asyncio
import websockets

@asyncio.coroutine
def hello():
    websocket = yield from websockets.connect('ws://192.168.1.106:81/')
    ws = yield from websockets.connect('ws://192.168.1.107:81/')
    while True:
        try:
            option = input("What Do you want to do? ")
            if option == "Led on":
                yield from websocket.send(option)
                print("> {}".format(option))

                greeting = yield from websocket.recv()
                print("< {}".format(greeting))

            elif option == "Led off":
                yield from websocket.send(option)
                print("> {}".format(option))

                greeting = yield from websocket.recv()
                print("< {}".format(greeting))
            elif option == "Lamp on":
                yield from websocket.send(option)
                print("> {}".format(option))

                greeting = yield from websocket.recv()
                print("< {}".format(greeting))

            elif option == "Lamp off":
                yield from websocket.send(option)
                print("> {}".format(option))

                greeting = yield from websocket.recv()
                print("< {}".format(greeting))

            elif option == "Computer on":
                yield from ws.send(option)
                print("> {}".format(option))

                greeting = yield from ws.recv()
                print("< {}".format(greeting))

            elif option == "Computer off":
                yield from ws.send(option)
                print("> {}".format(option))

                greeting = yield from ws.recv()
                print("< {}".format(greeting))

            elif option == "Exit" or option == "quit":
                break
            else:
                print("Invalid option")


        finally:
            print("")
    yield from websocket.close()
    yield from ws.close()


asyncio.get_event_loop().run_until_complete(hello())