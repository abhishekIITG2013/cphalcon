
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "ext/spl/spl_exceptions.h"


/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2014 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 +------------------------------------------------------------------------+
 */
/**
 * Phalcon\Validation\Validator\Email
 *
 * Checks if a value has a correct e-mail format
 *
 *<code>
 *use Phalcon\Validation\Validator\Email as EmailValidator;
 *
 *$validator->add('email', new EmailValidator(array(
 *   'message' => 'The e-mail is not valid'
 *)));
 *</code>
 */
ZEPHIR_INIT_CLASS(Phalcon_Validation_Validator_Email) {

	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Validation\\Validator, Email, phalcon, validation_validator_email, phalcon_validation_validator_ce, phalcon_validation_validator_email_method_entry, 0);

	zend_class_implements(phalcon_validation_validator_email_ce TSRMLS_CC, 1, phalcon_validation_validatorinterface_ce);
	return SUCCESS;

}

/**
 * Executes the validation
 *
 * @param  Phalcon\Validation validation
 * @param  string             field
 * @return boolean
 */
PHP_METHOD(Phalcon_Validation_Validator_Email, validate) {

	zend_bool _2;
	zval *field = NULL;
	zval *validation, *field_param = NULL, *value, *message = NULL, *label = NULL, *replacePairs, *_0, *_1, _3, *_4 = NULL, *_5, *_6;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &validation, &field_param);

	if (Z_TYPE_P(field_param) != IS_STRING && Z_TYPE_P(field_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'field' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(field_param) == IS_STRING) {
		field = field_param;
	} else {
		ZEPHIR_INIT_VAR(field);
		ZVAL_EMPTY_STRING(field);
	}


	if (!(zephir_instance_of_ev(validation, phalcon_validation_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(spl_ce_InvalidArgumentException, "Parameter 'validation' must be an instance of 'Phalcon\\Validation'");
		return;
	}
	ZEPHIR_INIT_VAR(value);
	zephir_call_method_p1(value, validation, "getvalue", field);
	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "allowEmpty", 1);
	zephir_call_method_p1(_0, this_ptr, "issetoption", _1);
	_2 = zephir_is_true(_0);
	if (_2) {
		_2 = ZEPHIR_IS_EMPTY(value);
	}
	if (_2) {
		RETURN_MM_BOOL(1);
	}
	ZEPHIR_SINIT_VAR(_3);
	ZVAL_LONG(&_3, 274);
	ZEPHIR_INIT_BNVAR(_1);
	zephir_call_func_p2(_1, "filter_var", value, &_3);
	if (!(zephir_is_true(_1))) {
		ZEPHIR_INIT_VAR(_4);
		ZVAL_STRING(_4, "label", 1);
		ZEPHIR_INIT_VAR(label);
		zephir_call_method_p1(label, this_ptr, "getoption", _4);
		if (ZEPHIR_IS_EMPTY(label)) {
			ZEPHIR_INIT_NVAR(label);
			zephir_call_method_p1(label, validation, "getlabel", field);
			if (ZEPHIR_IS_EMPTY(label)) {
				ZEPHIR_CPY_WRT(label, field);
			}
		}
		ZEPHIR_INIT_NVAR(_4);
		ZVAL_STRING(_4, "message", 1);
		ZEPHIR_INIT_VAR(message);
		zephir_call_method_p1(message, this_ptr, "getoption", _4);
		ZEPHIR_INIT_VAR(replacePairs);
		array_init_size(replacePairs, 2);
		zephir_array_update_string(&replacePairs, SL(":field"), &label, PH_COPY | PH_SEPARATE);
		if (ZEPHIR_IS_EMPTY(message)) {
			ZEPHIR_INIT_NVAR(_4);
			ZVAL_STRING(_4, "Email", 1);
			ZEPHIR_INIT_NVAR(message);
			zephir_call_method_p1(message, validation, "getdefaultmessage", _4);
		}
		ZEPHIR_INIT_VAR(_5);
		object_init_ex(_5, phalcon_validation_message_ce);
		ZEPHIR_INIT_NVAR(_4);
		zephir_call_func_p2(_4, "strtr", message, replacePairs);
		ZEPHIR_INIT_VAR(_6);
		ZVAL_STRING(_6, "Email", 1);
		zephir_call_method_p3_noret(_5, "__construct", _4, field, _6);
		zephir_call_method_p1_noret(validation, "appendmessage", _5);
		RETURN_MM_BOOL(0);
	}
	RETURN_MM_BOOL(1);

}

