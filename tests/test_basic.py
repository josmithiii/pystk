import pystk

def test_samplerate():
    sr = 41919
    pystk.set_sample_rate(sr)
    assert pystk.sample_rate() == sr