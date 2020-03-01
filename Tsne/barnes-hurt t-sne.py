import numpy as np
from scipy import linalg
from time import time

def point_wise_dist(X0, X1):
    assert(X0.shape[0]== X1.shape[0])
    # now we simply assume that two data has the same dimensionalities
    assert(X0.shape[1]== X1.shape[1])
    # '''(a-b)^2 = a^2 + b^2 - 2*a*b'''
    # sum_x = np.sum(np.square(x), 1)
    # dist = np.add(np.add(-2 * np.dot(x, x.T), sum_x).T, sum_x)
    D = np.zeros(X0.shape[0])
    for i in range(X0.shape[0]):
            D[i] = np.sum(np.square(X0[i,:]-X1[i, :]))

    return D


def joint_tsne_obj():
    error
    return error

def cal_pairwise_dist(x):
    '''(a-b)^2 = a^2 + b^2 - 2*a*b'''
    sum_x = np.sum(np.square(x), 1)
    dist = np.add(np.add(-2 * np.dot(x, x.T), sum_x).T, sum_x)
    return dist



def Hbeta(D=np.array([]), beta=1.0):
    """
        Compute the perplexity and the P-row for a specific value of the
        precision of a Gaussian distribution.
    """

    # Compute P-row and corresponding perplexity
    P = np.exp(-D.copy() * beta)
    sumP = sum(P)
    H = np.log(sumP) + beta * np.sum(D * P) / sumP
    P = P / sumP
    return H, P

def NearestNeighbors():
    pass


def pca(X=np.array([]), no_dims=50):
    """
        Runs PCA on the NxD array X in order to reduce its dimensionality to
        no_dims dimensions.
    """

    print("Preprocessing the data using PCA...")
    (n, d) = X.shape
    X = X - np.tile(np.mean(X, 0), (n, 1))
    (l, M) = np.linalg.eig(np.dot(X.T, X))
    Y = np.dot(X, M[:, 0:no_dims])
    return Y


def x2p(X=np.array([]), tol=1e-5, perplexity=30.0):
    """
        Performs a binary search to get P-values in such a way that each
        conditional Gaussian has the same perplexity.
    """

    # Initialize some variables
    print("Computing pairwise distances...")
    (n, d) = X.shape
    D = cal_pairwise_dist(X)
    P = np.zeros((n, n))
    beta = np.ones((n, 1))
    logU = np.log(perplexity)

    # Loop over all datapoints
    for i in range(n):

        # Print progress
        if i % 500 == 0:
            print("Computing P-values for point %d of %d..." % (i, n))

        # Compute the Gaussian kernel and entropy for the current precision
        betamin = -np.inf
        betamax = np.inf
        Di = D[i, np.concatenate((np.r_[0:i], np.r_[i+1:n]))]
        (H, thisP) = Hbeta(Di, beta[i])

        # Evaluate whether the perplexity is within tolerance
        Hdiff = H - logU
        tries = 0
        while np.abs(Hdiff) > tol and tries < 50:

            # If not, increase or decrease precision
            if Hdiff > 0:
                betamin = beta[i].copy()
                if betamax == np.inf or betamax == -np.inf:
                    beta[i] = beta[i] * 2.
                else:
                    beta[i] = (beta[i] + betamax) / 2.
            else:
                betamax = beta[i].copy()
                if betamin == np.inf or betamin == -np.inf:
                    beta[i] = beta[i] / 2.
                else:
                    beta[i] = (beta[i] + betamin) / 2.

            # Recompute the values
            (H, thisP) = Hbeta(Di, beta[i])
            Hdiff = H - logU
            tries += 1

        # Set the final row of P
        P[i, np.concatenate((np.r_[0:i], np.r_[i+1:n]))] = thisP

    # Return final P-matrix
    print("Mean value of sigma: %f" % np.mean(np.sqrt(1 / beta)))
    return P



def _kl_divergence_bh(params, P, degrees_of_freedom, n_samples, n_components,
                      angle=0.5, skip_num_points=0, verbose=False,
                      compute_error=True, num_threads=1):
    """t-SNE objective function: KL divergence of p_ijs and q_ijs.

    Uses Barnes-Hut tree methods to calculate the gradient that
    runs in O(NlogN) instead of O(N^2)

    Parameters
    ----------
    params : array, shape (n_params,)
        Unraveled embedding.

    P : csr sparse matrix, shape (n_samples, n_sample)
        Sparse approximate joint probability matrix, computed only for the
        k nearest-neighbors and symmetrized.

    degrees_of_freedom : int
        Degrees of freedom of the Student's-t distribution.

    n_samples : int
        Number of samples.

    n_components : int
        Dimension of the embedded space.

    angle : float (default: 0.5)
        This is the trade-off between speed and accuracy for Barnes-Hut T-SNE.
        'angle' is the angular size (referred to as theta in [3]) of a distant
        node as measured from a point. If this size is below 'angle' then it is
        used as a summary node of all points contained within it.
        This method is not very sensitive to changes in this parameter
        in the range of 0.2 - 0.8. Angle less than 0.2 has quickly increasing
        computation time and angle greater 0.8 has quickly increasing error.

    skip_num_points : int (optional, default:0)
        This does not compute the gradient for points with indices below
        `skip_num_points`. This is useful when computing transforms of new
        data where you'd like to keep the old data fixed.

    verbose : int
        Verbosity level.

    compute_error: bool (optional, default:True)
        If False, the kl_divergence is not computed and returns NaN.

    num_threads : int (optional, default:1)
        Number of threads used to compute the gradient. This is set here to
        avoid calling _openmp_effective_n_threads for each gradient step.

    Returns
    -------
    kl_divergence : float
        Kullback-Leibler divergence of p_ij and q_ij.

    grad : array, shape (n_params,)
        Unraveled gradient of the Kullback-Leibler divergence with respect to
        the embedding.
    """
    params = params.astype(np.float32, copy=False)
    X_embedded = params.reshape(n_samples, n_components)

    val_P = P.data.astype(np.float32, copy=False)
    neighbors = P.indices.astype(np.int64, copy=False)
    indptr = P.indptr.astype(np.int64, copy=False)

    grad = np.zeros(X_embedded.shape, dtype=np.float32)
    error = joint_tsne_obj(val_P, X_embedded, neighbors, indptr,
                                      grad, angle, n_components, verbose,
                                      dof=degrees_of_freedom,
                                      compute_error=compute_error,
                                      num_threads=num_threads)
    c = 2.0 * (degrees_of_freedom + 1.0) / degrees_of_freedom
    grad = grad.ravel()
    grad *= c

    return error, grad

def _joint_probabilities_nn(distances, desired_perplexity, verbose):
    """Compute joint probabilities p_ij from distances using just nearest
    neighbors.

    This method is approximately equal to _joint_probabilities. The latter
    is O(N), but limiting the joint probability to nearest neighbors improves
    this substantially to O(uN).

    Parameters
    ----------
    distances : CSR sparse matrix, shape (n_samples, n_samples)
        Distances of samples to its n_neighbors nearest neighbors. All other
        distances are left to zero (and are not materialized in memory).

    desired_perplexity : float
        Desired perplexity of the joint probability distributions.

    verbose : int
        Verbosity level.

    Returns
    -------
    P : csr sparse matrix, shape (n_samples, n_samples)
        Condensed joint probability matrix with only nearest neighbors.
    """
    t0 = time()
    # Compute conditional probabilities such that they approximately match
    # the desired perplexity
    distances.sort_indices()
    n_samples = distances.shape[0]
    distances_data = distances.data.reshape(n_samples, -1)
    distances_data = distances_data.astype(np.float32, copy=False)
    P = x2p(
        distances_data, verbose, desired_perplexity)
    assert np.all(np.isfinite(P)), \
        "All probabilities should be finite"

    # Symmetrize the joint probability distribution using sparse operations
    P = P + np.transpose(P)
    # P = P / np.sum(P)
    # P = csr_matrix((conditional_P.ravel(), distances.indices,
    #                 distances.indptr),
    #                shape=(n_samples, n_samples))
    # P = P + P.T

    # Normalize the joint probability distribution
    sum_P = np.maximum(P.sum(), 1e-12)
    P /= sum_P

    # assert np.all(np.abs(P.data) <= 1.0)
    if verbose >= 2:
        duration = time() - t0
        print("[t-SNE] Computed conditional probabilities in {:.3f}s"
              .format(duration))
    return P

def _gradient_descent(objective, p0, it, n_iter,
                      n_iter_check=1, n_iter_without_progress=300,
                      momentum=0.8, learning_rate=200.0, min_gain=0.01,
                      min_grad_norm=1e-7, verbose=0, args=None, kwargs=None):
    """Batch gradient descent with momentum and individual gains.

    Parameters
    ----------
    objective : function or callable
        Should return a tuple of cost and gradient for a given parameter
        vector. When expensive to compute, the cost can optionally
        be None and can be computed every n_iter_check steps using
        the objective_error function.

    p0 : array-like, shape (n_params,)
        Initial parameter vector.

    it : int
        Current number of iterations (this function will be called more than
        once during the optimization).

    n_iter : int
        Maximum number of gradient descent iterations.

    n_iter_check : int
        Number of iterations before evaluating the global error. If the error
        is sufficiently low, we abort the optimization.

    n_iter_without_progress : int, optional (default: 300)
        Maximum number of iterations without progress before we abort the
        optimization.

    momentum : float, within (0.0, 1.0), optional (default: 0.8)
        The momentum generates a weight for previous gradients that decays
        exponentially.

    learning_rate : float, optional (default: 200.0)
        The learning rate for t-SNE is usually in the range [10.0, 1000.0]. If
        the learning rate is too high, the data may look like a 'ball' with any
        point approximately equidistant from its nearest neighbours. If the
        learning rate is too low, most points may look compressed in a dense
        cloud with few outliers.

    min_gain : float, optional (default: 0.01)
        Minimum individual gain for each parameter.

    min_grad_norm : float, optional (default: 1e-7)
        If the gradient norm is below this threshold, the optimization will
        be aborted.

    verbose : int, optional (default: 0)
        Verbosity level.

    args : sequence
        Arguments to pass to objective function.

    kwargs : dict
        Keyword arguments to pass to objective function.

    Returns
    -------
    p : array, shape (n_params,)
        Optimum parameters.

    error : float
        Optimum.

    i : int
        Last iteration.
    """
    if args is None:
        args = []
    if kwargs is None:
        kwargs = {}

    p = p0.copy().ravel()
    update = np.zeros_like(p)
    gains = np.ones_like(p)
    error = np.finfo(np.float).max
    best_error = np.finfo(np.float).max
    best_iter = i = it

    tic = time()
    for i in range(it, n_iter):
        check_convergence = (i + 1) % n_iter_check == 0
        # only compute the error when needed
        kwargs['compute_error'] = check_convergence or i == n_iter - 1

        error, grad = objective(p, *args, **kwargs)
        grad_norm = linalg.norm(grad)

        inc = update * grad < 0.0
        dec = np.invert(inc)
        gains[inc] += 0.2
        gains[dec] *= 0.8
        np.clip(gains, min_gain, np.inf, out=gains)
        grad *= gains
        update = momentum * update - learning_rate * grad
        p += update

        if check_convergence:
            toc = time()
            duration = toc - tic
            tic = toc

            if verbose >= 2:
                print("[t-SNE] Iteration %d: error = %.7f,"
                      " gradient norm = %.7f"
                      " (%s iterations in %0.3fs)"
                      % (i + 1, error, grad_norm, n_iter_check, duration))

            if error < best_error:
                best_error = error
                best_iter = i
            elif i - best_iter > n_iter_without_progress:
                if verbose >= 2:
                    print("[t-SNE] Iteration %d: did not make any progress "
                          "during the last %d episodes. Finished."
                          % (i + 1, n_iter_without_progress))
                break
            if grad_norm <= min_grad_norm:
                if verbose >= 2:
                    print("[t-SNE] Iteration %d: gradient norm %f. Finished."
                          % (i + 1, grad_norm))
                break

    return p, error, i


def check_random_state(seed):
    """Turn seed into a np.random.RandomState instance

    Parameters
    ----------
    seed : None | int | instance of RandomState
        If seed is None, return the RandomState singleton used by np.random.
        If seed is an int, return a new RandomState instance seeded with seed.
        If seed is already a RandomState instance, return it.
        Otherwise raise ValueError.
    """
    if seed is None or seed is np.random:
        return np.random.mtrand._rand
    if isinstance(seed, numbers.Integral):
        return np.random.RandomState(seed)
    if isinstance(seed, np.random.RandomState):
        return seed
    raise ValueError('%r cannot be used to seed a numpy.random.RandomState'
                     ' instance' % seed)

class BH_TSNE():
    # Control the number of exploration iterations with early_exaggeration on
    _EXPLORATION_N_ITER = 250

    # Control the number of iterations between progress checks
    _N_ITER_CHECK = 50

    def __init__(self, n_components=2, perplexity=30.0,
                 early_exaggeration=12.0, learning_rate=200.0, n_iter=1000,
                 n_iter_without_progress=300, min_grad_norm=1e-7,
                 metric="euclidean", init="random", verbose=0,
                 random_state=None, method='barnes_hut', angle=0.5,
                 n_jobs=None):
        self.n_components = n_components
        self.perplexity = perplexity
        self.early_exaggeration = early_exaggeration
        self.learning_rate = learning_rate
        self.n_iter = n_iter
        self.n_iter_without_progress = n_iter_without_progress
        self.min_grad_norm = min_grad_norm
        self.metric = metric
        self.init = init
        self.verbose = verbose
        self.random_state = random_state
        self.method = method
        self.angle = angle
        self.n_jobs = n_jobs

    def _fit(self, X, skip_num_points=0):
        """Private function to fit the model using X as training data."""

        if self.method not in ['barnes_hut', 'exact']:
            raise ValueError("'method' must be 'barnes_hut' or 'exact'")
        if self.angle < 0.0 or self.angle > 1.0:
            raise ValueError("'angle' must be between 0.0 - 1.0")
        if self.method == 'barnes_hut':
            X = check_array(X, accept_sparse=['csr'], ensure_min_samples=2,
                            dtype=[np.float32, np.float64])
        if self.metric == "precomputed":
            if isinstance(self.init, str) and self.init == 'pca':
                raise ValueError("The parameter init=\"pca\" cannot be "
                                 "used with metric=\"precomputed\".")
            if X.shape[0] != X.shape[1]:
                raise ValueError("X should be a square distance matrix")

            # check_non_negative(X, "TSNE.fit(). With metric='precomputed', X "
            #                       "should contain positive distances.")

            # if self.method == "exact" and issparse(X):
            #     raise TypeError(
            #         'TSNE with method="exact" does not accept sparse '
            #         'precomputed distance matrix. Use method="barnes_hut" '
            #         'or provide the dense distance matrix.')

        if self.method == 'barnes_hut' and self.n_components > 3:
            raise ValueError("'n_components' should be inferior to 4 for the "
                             "barnes_hut algorithm as it relies on "
                             "quad-tree or oct-tree.")
        random_state = check_random_state(self.random_state)

        if self.early_exaggeration < 1.0:
            raise ValueError("early_exaggeration must be at least 1, but is {}"
                             .format(self.early_exaggeration))

        if self.n_iter < 250:
            raise ValueError("n_iter should be at least 250")

        n_samples = X.shape[0]

        neighbors_nn = None

        # Compute the number of nearest neighbors to find.
        # LvdM uses 3 * perplexity as the number of neighbors.
        # In the event that we have very small # of points
        # set the neighbors to n - 1.
        n_neighbors = min(n_samples - 1, int(3. * self.perplexity + 1))

        if self.verbose:
            print("[t-SNE] Computing {} nearest neighbors..."
                    .format(n_neighbors))

        # Find the nearest neighbors for every point
        knn = NearestNeighbors(algorithm='auto',
                                n_jobs=self.n_jobs,
                                n_neighbors=n_neighbors,
                                metric=self.metric)
        t0 = time()
        knn.fit(X)
        duration = time() - t0
        if self.verbose:
            print("[t-SNE] Indexed {} samples in {:.3f}s...".format(
                n_samples, duration))

        t0 = time()
        distances_nn = knn.kneighbors_graph(mode='distance')
        duration = time() - t0
        if self.verbose:
            print("[t-SNE] Computed neighbors for {} samples "
                    "in {:.3f}s...".format(n_samples, duration))

        # Free the memory used by the ball_tree
        del knn

        if self.metric == "euclidean":
            # knn return the euclidean distance but we need it squared
            # to be consistent with the 'exact' method. Note that the
            # the method was derived using the euclidean method as in the
            # input space. Not sure of the implication of using a different
            # metric.
            distances_nn.data **= 2

        # compute the joint probability distribution for the input space
        P = _joint_probabilities_nn(distances_nn, self.perplexity,
                                    self.verbose)

        if isinstance(self.init, np.ndarray):
            X_embedded = self.init
        elif self.init == 'pca':
            # pca = PCA(n_components=self.n_components, svd_solver='randomized',
            #           random_state=random_state)
            # X_embedded = pca.fit_transform(X).astype(np.float32, copy=False)
            X_embedded = pca(X, initial_dims)
        elif self.init == 'random':
            # The embedding is initialized with iid samples from Gaussians with
            # standard deviation 1e-4.
            X_embedded = 1e-4 * random_state.randn(
                n_samples, self.n_components).astype(np.float32)
        else:
            raise ValueError("'init' must be 'pca', 'random', or "
                             "a numpy array")

        # Degrees of freedom of the Student's t-distribution. The suggestion
        # degrees_of_freedom = n_components - 1 comes from
        # "Learning a Parametric Embedding by Preserving Local Structure"
        # Laurens van der Maaten, 2009.
        degrees_of_freedom = max(self.n_components - 1, 1)

        return self._tsne(P, degrees_of_freedom, n_samples,
                          X_embedded=X_embedded,
                          neighbors=neighbors_nn,
                          skip_num_points=skip_num_points)

    def _tsne(self, P, degrees_of_freedom, n_samples, X_embedded,
              neighbors=None, skip_num_points=0):
        """Runs t-SNE."""
        # t-SNE minimizes the Kullback-Leiber divergence of the Gaussians P
        # and the Student's t-distributions Q. The optimization algorithm that
        # we use is batch gradient descent with two stages:
        # * initial optimization with early exaggeration and momentum at 0.5
        # * final optimization with momentum at 0.8
        params = X_embedded.ravel()

        opt_args = {
            "it": 0,
            "n_iter_check": self._N_ITER_CHECK,
            "min_grad_norm": self.min_grad_norm,
            "learning_rate": self.learning_rate,
            "verbose": self.verbose,
            "kwargs": dict(skip_num_points=skip_num_points),
            "args": [P, degrees_of_freedom, n_samples, self.n_components],
            "n_iter_without_progress": self._EXPLORATION_N_ITER,
            "n_iter": self._EXPLORATION_N_ITER,
            "momentum": 0.5,
        }
        if self.method == 'barnes_hut':
            obj_func = _kl_divergence_bh
            opt_args['kwargs']['angle'] = self.angle
            # Repeat verbose argument for _kl_divergence_bh
            opt_args['kwargs']['verbose'] = self.verbose

        # Learning schedule (part 1): do 250 iteration with lower momentum but
        # higher learning rate controlled via the early exaggeration parameter
        P *= self.early_exaggeration
        params, kl_divergence, it = _gradient_descent(obj_func, params,
                                                      **opt_args)
        if self.verbose:
            print("[t-SNE] KL divergence after %d iterations with early "
                  "exaggeration: %f" % (it + 1, kl_divergence))

        # Learning schedule (part 2): disable early exaggeration and finish
        # optimization with a higher momentum at 0.8
        P /= self.early_exaggeration
        remaining = self.n_iter - self._EXPLORATION_N_ITER
        if it < self._EXPLORATION_N_ITER or remaining > 0:
            opt_args['n_iter'] = self.n_iter
            opt_args['it'] = it + 1
            opt_args['momentum'] = 0.8
            opt_args['n_iter_without_progress'] = self.n_iter_without_progress
            params, kl_divergence, it = _gradient_descent(obj_func, params,
                                                          **opt_args)

        # Save the final number of iterations
        self.n_iter_ = it

        if self.verbose:
            print("[t-SNE] KL divergence after %d iterations: %f"
                  % (it + 1, kl_divergence))

        X_embedded = params.reshape(n_samples, self.n_components)
        self.kl_divergence_ = kl_divergence

        return X_embedded

    def fit_transform(self, X, y=None):
        """Fit X into an embedded space and return that transformed
        output.

        Parameters
        ----------
        X : array, shape (n_samples, n_features) or (n_samples, n_samples)
            If the metric is 'precomputed' X must be a square distance
            matrix. Otherwise it contains a sample per row. If the method
            is 'exact', X may be a sparse matrix of type 'csr', 'csc'
            or 'coo'. If the method is 'barnes_hut' and the metric is
            'precomputed', X may be a precomputed sparse graph.

        y : Ignored

        Returns
        -------
        X_new : array, shape (n_samples, n_components)
            Embedding of the training data in low-dimensional space.
        """
        embedding = self._fit(X)
        self.embedding_ = embedding
        return self.embedding_

    def fit(self, X, y=None):
        """Fit X into an embedded space.

        Parameters
        ----------
        X : array, shape (n_samples, n_features) or (n_samples, n_samples)
            If the metric is 'precomputed' X must be a square distance
            matrix. Otherwise it contains a sample per row. If the method
            is 'exact', X may be a sparse matrix of type 'csr', 'csc'
            or 'coo'. If the method is 'barnes_hut' and the metric is
            'precomputed', X may be a precomputed sparse graph.

        y : Ignored
        """
        self.fit_transform(X)
        return self
