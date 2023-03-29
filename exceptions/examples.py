import showcase

try:
    raise showcase.MyFancyError("message")
except showcase.MyError as e:
    print(e)
