from random import choice, randint

DEFAULT_LOCALE = 'en'
LOCALES = ('en', 'ru')
MIN_LENGTH = 6
MAX_LENGTH = 9

en_vowels = ('a', 'e', 'i', 'o', 'u', 'y')
en_consonants = ('b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z',
                 'sh', 'zh', 'ch', 'kh', 'th')
ru_vowels = ('а', 'е', 'и', 'о', 'у', 'э', 'ю', 'я')
ru_consonants = ('б', 'в', 'г', 'д', 'ж', 'з', 'к', 'л', 'м',
                 'н', 'п', 'р', 'с', 'т', 'ф', 'х', 'ц', 'ч', 'ш', 'щ')


def generate(locale=None):
    """
    Generates nickname
    :param str locale:
    :rtype: str
    :return:
    """
    if locale is None or locale not in LOCALES:
        locale = DEFAULT_LOCALE

    vowels = globals()['{}_vowels'.format(locale)]
    consonants = globals()['{}_consonants'.format(locale)]

    is_vowels_first = bool(randint(0, 1))
    result = ''
    for i in range(0, randint(MIN_LENGTH, MAX_LENGTH)):
        is_even = i % 2 is 0
        if (is_vowels_first and is_even) or (not is_vowels_first and not is_even):
            result += choice(vowels)
        else:
            result += choice(consonants)

    return result.title()
