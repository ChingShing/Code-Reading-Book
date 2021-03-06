eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# exhaustive_test.pl,v 1.3 2001/03/05 03:23:47 brunsch Exp
# -*- perl -*-

# This is a Perl script that runs the client and all the other servers that
# are needed

use lib '../../../../../bin';
use PerlACE::Run_Test;

$status = 0;

$conf_file = PerlACE::LocalFile ('exhaustive.conf');

@dispatching_configs   = ("-ECDispatching reactive",
                          "-ECDispatching mt -ECDispatchingThreads 4");
@collection_strategies = ("copy_on_read", 
                          "copy_on_write", 
                          "delayed");
@collection_types      = ("list", 
                          "rb_tree");
@filtering_configs     = ("-ECFiltering prefix -ECSupplierFilter per-supplier",
                          "-ECFiltering prefix -ECSupplierFilter null");

foreach $d (@dispatching_configs) {
    foreach $f (@filtering_configs) {
        foreach $c (@collection_strategies) {
            foreach $t (@collection_types) {
                my $collection = "mt:".$c.":".$t;
                
                my $config = 'static EC_Factory "'
                             .$d
                             ." -ECProxyPushConsumerCollection ".$collection
                             ." -ECProxyPushSupplierCollection ".$collection
                             ." ".$f
                             .'"';

                open (CONFIG,">$conf_file") || die "Cannot open $conf_file\n";
                print CONFIG $config, "\n";
                close (CONFIG);

                print STDERR "\n\n", $config, "\n";

                system ("purify.exe "
                        . "/run .\\Release\\Random.exe "
                        . " -ORBSvcConf $conf_file"
                        . " -suppliers 16"
                        . " -consumers 16"
                        . " -max_recursion 0");
            }
        }
    }
}

unlink "$conf_file";

exit $status;
