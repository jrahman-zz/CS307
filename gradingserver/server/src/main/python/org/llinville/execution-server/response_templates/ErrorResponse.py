class ErrorResponse:

    def __init__(self):
        self.messages = []

    def addmessage(self, messagetype, message):
        self.messages.append((messagetype, message))