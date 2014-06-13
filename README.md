alembia
=======

ALE/MBIA - Two simple encapsulated symmetric-key ciphers, 512-bit overall key length

ALE/MBIA is an encapsulation of two (relatively simple) experimental ciphers - ALE (Additional Layer of Encryption)
and MBIA (Motivated By Intelligence Amok). They are EXPERIMENTAL and currently not meant to be used in security
critical environments.

The basic idea behind the concept is: Key length before algorithmic complexity.
Both algorithms use relatively basic cryptographic methods and are supposed to be easy to implement in hard- and
software. The hope is that at least one of the two algorithms is resistant to cryptanalysis and the only remaining
method to crack the encryption is brute forcing. Brute forcing will be extremely difficult as two 256-bit long
symmetric keys will have to be cracked - one for the "outer" algorithm (ALE) and one for the "inner" algorithm (MBIA).
  