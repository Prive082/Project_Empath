import cv2

def penis():
    cam = cv2.VideoCapture(0, cv2.CAP_DSHOW)
    cam.set(cv2.CAP_PROP_FPS, 60)
    retval, frame = cam.read()
    if retval != True:
        raise ValueError("Can't read frame")

    cv2.imwrite('img4.png', frame)
