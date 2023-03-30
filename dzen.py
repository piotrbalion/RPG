num = 0
num2 = 0

while num < 100:
    if num2 == 1:
        print('liczba {0} jest nieparzysta'.format(num))
    elif num2 == 0:
        print('liczba {0} jest parzysta'.format(num))
    else:
        print('numerek jest z dupy')
    num = num + 1
    num2 = num % 2 
    


    