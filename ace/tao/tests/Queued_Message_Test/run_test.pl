eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# run_test.pl,v 1.1 2001/05/02 14:15:51 coryan Exp
# -*- perl -*-

use lib '../../../bin';
use PerlACE::Run_Test;

$status = 0;

$T = new PerlACE::Process ("Queued_Message_Test");

$test = $T->SpawnWaitKill (60);

if ($test != 0) {
    print STDERR "ERROR: test returned $test\n";
    $status = 1;
}

exit $status;
