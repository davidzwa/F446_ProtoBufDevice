from math import comb


def P(m, n, r, q):
    p = 1.0
    for i in range(0, n+r):
        p *= (1 - 1 / pow(q, m-i))
    return p


def pmf_binomial_prob(p_error, m, N):
    return comb(N, m) * pow(p_error, N - m) * pow(1-p_error, m)


def failure_rate(n, N, eps, q, include_rref, r=0):
    p_success = 0
    for m in range(n, N+1):
        rref_failure_prob = P(m, n, r, q)

        # Calculate PER failure probability
        per_failure_prob = pmf_binomial_prob(eps, m, N)

        # Include row-reduction failure probability
        if include_rref:
            p_success += per_failure_prob * rref_failure_prob
        else:
            p_success += per_failure_prob

    return 1 - p_success


def failure_rates(n, delta_max, PER, q, include_rref):
    redundancies = range(0, delta_max+1)

    failure_probs = []
    for delta in redundancies:
        failure_probs.append(failure_rate(n, n+delta, PER, 0, q, include_rref))

    return redundancies, failure_probs


def success_rates(n, delta_max, PER, q, include_rref):
    redundancies = range(0, delta_max+1)

    success_probs = []
    for delta in redundancies:
        success_probs.append(
            1 - failure_rate(n, n+delta, PER, 0, q, include_rref))

    return redundancies, success_probs
