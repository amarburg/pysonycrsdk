import sonycrsdk as m


def test_enumerate():
    a = m.Camera.Enumerate()
    print(a)
